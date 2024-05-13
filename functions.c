#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>
#include <SDL/SDL_ttf.h>

SDL_Surface *sunImages[4];
SDL_Rect sunPos;
void loadtext1(char text[] , char cheminfont[], int taille , int indcouleur, int x , int y , SDL_Surface *ecran) { // 1 red , 2 green , 3 blue , 0 white , -1 black 
	SDL_Surface *txtsurf;
	SDL_Rect postxtEcran;
	TTF_Font *font;
	SDL_Color txtcolor;
	 switch(indcouleur) {
	 	case 1:
	 	txtcolor.r=150;
	 	txtcolor.g=0;
	 	txtcolor.b=0;
	 	break;
	 	case 2:
	 	txtcolor.r =0;
	 	txtcolor.g=120;
	 	txtcolor.b=0;
	 	break;
	 	case 3:
	 	txtcolor.r=0;
	 	txtcolor.g=0;
	 	txtcolor.b=90;
	 	break;
	 	case 0:
	 	txtcolor.r=150;
	 	txtcolor.g=120;
	 	txtcolor.b=90;
	 	break;
	 	case -1:
	 	txtcolor.r=0;
	 	txtcolor.g=0;
	 	txtcolor.b=0;
	 	break;
	 }
	 postxtEcran.x=x;
	 postxtEcran.y=y;
	 font = TTF_OpenFont(cheminfont,taille);
	 if ( font ==NULL) {
	 	printf("ERROR LOADING FONT\n");
	 }
	 txtsurf=TTF_RenderText_Solid(font,text,txtcolor);
	 if (txtsurf==NULL) {
	 	printf("ERROR LOADING TEXT\n");
	 }
	 
	 SDL_BlitSurface(txtsurf,NULL,ecran,&postxtEcran);
	 
	
}
int compareInts(const void *a, const void *b) {
    int intA = *((int*)a);
    int intB = *((int*)b);
    
    if (intA < intB) return -1;
    else if (intA > intB) return 1;
    else return 0;
}

void saveScore(int score) {
    FILE *file = fopen("score.txt", "a");
    if (file) {
        fprintf(file, "%d ", score);
        fclose(file);
    } else {
        fprintf(stderr, "Failed to open scores file for writing.\n");
    }
}

 

int readLastScore() {
    FILE *file = fopen("score.txt", "r");
    if (file) {
        int lastScore;
        while (fscanf(file, "%d", &lastScore) != EOF) {
            // Read all scores until the last one
        }
        fclose(file);
        return lastScore;
    } else {
        fprintf(stderr, "Failed to open scores file for reading.\n");
        return -1; // Return -1 if failed to read
    }
}
void afficherScore(int score, SDL_Surface *backgroundSurface) {
    char scoreStr[20];
    sprintf(scoreStr, "Score: %d", score);

    TTF_Font *police = TTF_OpenFont("arial.ttf", 24);
    if (!police) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Color couleurTexte = {255, 255, 255}; // Blanc

    SDL_Surface *texteSurface = TTF_RenderText_Solid(police, scoreStr, couleurTexte);
    if (!texteSurface) {
        fprintf(stderr, "Failed to render text: %s\n", TTF_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Rect posTexte = {10, 10, 0, 0};

    SDL_BlitSurface(texteSurface, NULL, backgroundSurface, &posTexte);

    SDL_FreeSurface(texteSurface);
    TTF_CloseFont(police);
}
void displayHighScores() {
    FILE *file = fopen("scores.txt", "r");
    if (file) {
        int scores[100]; // Assuming a maximum of 100 scores
        int count = 0;
        while (fscanf(file, "%d", &scores[count]) != EOF && count < 100) {
            count++;
        }
        fclose(file);

        // Sort scores
        qsort(scores, count, sizeof(int), compareInts);

        // Display top 3 scores
        printf("Top 3 Scores:\n");
        for (int i = 0; i < count && i < 3; i++) {
            printf("%d. %d\n", i + 1, scores[i]);
        }
    } else {
        fprintf(stderr, "Failed to open scores file for reading.\n");
    }
}
char *lire_ligne(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", nom_fichier);
        return NULL;
    }

    char *ligne = NULL;
    size_t taille = 0;

    // Utilisation de getline pour lire une ligne à partir du fichier
    ssize_t longueur = getline(&ligne, &taille, fichier);
    fclose(fichier);

    if (longueur == -1) {
        fprintf(stderr, "Erreur lors de la lecture de la ligne du fichier %s\n", nom_fichier);
        return NULL;
    }

    return ligne;
}


int lire_scores_et_trouver_max(const char *fichier_scores, const char *fichier_rank1) {
    FILE *f_scores = fopen(fichier_scores, "r");
    if (f_scores == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", fichier_scores);
        return;
    }

    int max_score = -1;
    int score;
    // Lire chaque score et trouver le score maximum
    while (fscanf(f_scores, "%d", &score) != EOF) {
        if (score > max_score) {
            max_score = score;
        }
    }
    fclose(f_scores);

    FILE *f_rank1 = fopen(fichier_rank1, "w");
    if (f_rank1 == NULL) {
        printf("Impossible de créer le fichier %s\n", fichier_rank1);
        return;
    }
    // Écrire le score maximum dans rank1.txt
    fprintf(f_rank1, "%d", max_score);
    fclose(f_rank1);
return(max_score);
}

void initCamera(Camera *camera) {
    camera->x = 0;
    camera->y = 0;
    camera->w = LARGEUR_ECRAN;
    camera->h = HAUTEUR_ECRAN;
}

void loadSunImages() {
    for (int i = 0; i < 4; ++i) {
        char filename[20];
        sprintf(filename, "sun%d.png", i);
        sunImages[i] = IMG_Load(filename);
        if (!sunImages[i]) {
            fprintf(stderr, "Failed to load sun image: %s\n", IMG_GetError());
            SDL_Quit();
            exit(1);
        }
    }
}

SDL_Surface *loadImage(char *filename) {
    SDL_Surface *loadedImage = IMG_Load(filename);
    if (!loadedImage) {
        fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }
    return loadedImage;
}

void initialiserJoueur(Joueur *joueur, char *spritePath, int posX, int posY) {
    joueur->x = posX;
    joueur->y = posY;
    joueur->sprite = IMG_Load(spritePath);
    if (!joueur->sprite) {
        fprintf(stderr, "Failed to load player sprite: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }
}

void initialiserBackground(Background *background, char *imagePath) {
    background->image = loadImage(imagePath);
    if (!background->image) {
        fprintf(stderr, "Failed to load background image: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }
    
    background->posBack1.x = 0;
    background->posBack1.y = 0;
    background->posBack1.w = LARGEUR_ECRAN;
    background->posBack1.h = HAUTEUR_ECRAN;
    background->scrollX1 = 0;

    background->posBack2.x = LARGEUR_ECRAN;
    background->posBack2.y = 0;
    background->posBack2.w = LARGEUR_ECRAN;
    background->posBack2.h = HAUTEUR_ECRAN;
    background->scrollX2 = 0;

    background->posEcran.x = 0;
    background->posEcran.y = 0;
}

void afficherJoueur(Joueur *joueur) {
    SDL_Rect posJoueur = {joueur->x, joueur->y, LARGEUR_JOUEUR, HAUTEUR_JOUEUR};
    SDL_BlitSurface(joueur->sprite, NULL, screen, &posJoueur);
}

void afficherBackground(Background *background, int joueur) {
    if (joueur == 1) {
        background->posBack1.x = -background->scrollX1;
        SDL_BlitSurface(background->image, NULL, screen, &(background->posBack1));
    } else if (joueur == 2) {
        background->posBack2.x = LARGEUR_ECRAN - background->scrollX2;
        SDL_BlitSurface(background->image, NULL, screen, &(background->posBack2));
    }
}

void animerBack(int *frame) {
    SDL_BlitSurface(sunImages[*frame], NULL, screen, &sunPos);
    *frame = (*frame + 1) % 4;
}



//////
void dimenstionsBTN(SDL_Rect* btn1,SDL_Rect *btn2,SDL_Rect *btn3,SDL_Rect *btn4,SDL_Surface * btnclick0) {
	btn1->x=900;
	btn1->y=150;
	btn1->w=btnclick0->w;
	btn1->h=btnclick0->h;
        
        btn2->x=900;
	btn2->y=350;
	btn2->w=btnclick0->w;
	btn2->h=btnclick0->h;
	
	btn3->x=900;
	btn3->y=550;
	btn3->w=btnclick0->w;
	btn3->h=btnclick0->h;
	
	btn4->x=900;
	btn4->y=750;
	btn4->w=btnclick0->w;
	btn4->h=btnclick0->h;
	
	
}
bool sourisSurbtn(SDL_Rect btn, SDL_Event event) {
	if (event.motion.x >= btn.x && event.motion.x <= btn.x+btn.w && 
	event.motion.y >=btn.y && event.motion.y <= btn.y + btn.h) {
		return true;
	}
	else {
		return false;
	}
}
void changetexture(SDL_Rect btn1, SDL_Rect btn2, SDL_Rect btn3, SDL_Rect btn4, SDL_Event event, 
SDL_Surface * play1,
SDL_Surface * play2,
SDL_Surface * rank1,
SDL_Surface * rank2,
SDL_Surface * op1,
SDL_Surface * op2,
SDL_Surface * exit1,
SDL_Surface * exit2,
 SDL_Surface *ecran) {

	if (sourisSurbtn(btn1,event)) {
		SDL_BlitSurface(play1, NULL, ecran, &btn1);
	} else {
		SDL_BlitSurface(play2, NULL, ecran, &btn1); 
	}
	//
        if (sourisSurbtn(btn2,event)) {
		SDL_BlitSurface(rank1, NULL, ecran, &btn2);
	} else {	
		SDL_BlitSurface(rank2, NULL, ecran, &btn2); }
	//
	if (sourisSurbtn(btn3,event)) {
		SDL_BlitSurface(op1, NULL, ecran, &btn3);
	} else {	
		SDL_BlitSurface(op2, NULL, ecran, &btn3); }
	//
	
	if (sourisSurbtn(btn4,event)) {
		SDL_BlitSurface(exit1, NULL, ecran, &btn4);
	} else {
		SDL_BlitSurface(exit2, NULL, ecran, &btn4); 
	}
	//
	
	
}
void loadbtns(SDL_Surface **play1, SDL_Surface **play2 ,SDL_Surface **rank1, SDL_Surface **rank2 , SDL_Surface **op1, SDL_Surface **op2, SDL_Surface **exit1, SDL_Surface **exit2) {
	*play1=IMG_Load("play2.png");
	*play2=IMG_Load("play1.png");
	if ( *play1==NULL || *play2==NULL ) {
		printf("ERROR LOADING PLAY \n");
	}
        *rank1=IMG_Load("rank2.png");
	*rank2=IMG_Load("rank1.png");
	if ( *rank1==NULL || *rank2==NULL ) {
		printf("ERROR LOADING RANK \n");
	}
	*op1= IMG_Load("op2.png");
	*op2=IMG_Load("op1.png");
	if (*op1==NULL || *op2==NULL) {
		printf("ERROR LOADING OPTS \n");
	}
	*exit1=IMG_Load("exit2.png");
	*exit2=IMG_Load("exit1.png");
	if (*exit1==NULL || *exit2==NULL) {
		printf("ERORR LOADING QUIT\n");
	}

}
void loadlevel1(SDL_Surface *lvlback , SDL_Surface *ecran , SDL_Rect posback, Mix_Music *sonbref ) {
	SDL_Surface *surftxt;
	SDL_Rect postxt;
	TTF_Font *font;
	SDL_Color txtcolor;

	if ( TTF_Init() !=0 ) {
		printf("ERROR INITILIZING TEXT \n");
	}
	postxt.x=829;
	postxt.y=100;
	txtcolor.r=255;
	txtcolor.g=255;
	txtcolor.b=255;
	font=TTF_OpenFont("Marlboro.ttf",100);
	if (font ==NULL) {
		printf("Error loading font\n");
	}
	surftxt=TTF_RenderText_Solid(font,"Sands of serenity",txtcolor);
	
	lvlback=IMG_Load("test.png"); // taswira lezm tkoun 1920*1080 
	sonbref=Mix_LoadMUS("testlvl1.mp3");
	if (lvlback==NULL) {
		printf("ERORR LOADING TEST \n");
	} else if (sonbref ==NULL) {
		printf("ERROR LOADING SON BREF \n");
	}else {
	 
		
		printf("LEVEL 1 \n");
		posback.x=0;
		posback.y=0;
		posback.h=lvlback->h;
		posback.w=lvlback->w;
		SDL_BlitSurface (lvlback,NULL,ecran,&posback);
		SDL_BlitSurface(surftxt,NULL,ecran,&postxt);
		Mix_PlayMusic(sonbref,0);
		}
}
void loadtext(char text[] , char cheminfont[], int taille , int indcouleur, int x , int y , SDL_Surface *ecran) { // 1 red , 2 green , 3 blue , 0 white , -1 black 
	SDL_Surface *txtsurf;
	SDL_Rect postxtEcran;
	TTF_Font *font;
	SDL_Color txtcolor;
	 switch(indcouleur) {
	 	case 1:
	 	txtcolor.r=150;
	 	txtcolor.g=0;
	 	txtcolor.b=0;
	 	break;
	 	case 2:
	 	txtcolor.r =0;
	 	txtcolor.g=120;
	 	txtcolor.b=0;
	 	break;
	 	case 3:
	 	txtcolor.r=0;
	 	txtcolor.g=0;
	 	txtcolor.b=90;
	 	break;
	 	case 0:
	 	txtcolor.r=150;
	 	txtcolor.g=120;
	 	txtcolor.b=90;
	 	break;
	 	case -1:
	 	txtcolor.r=0;
	 	txtcolor.g=0;
	 	txtcolor.b=0;
	 	break;
	 }
	 postxtEcran.x=x;
	 postxtEcran.y=y;
	 font = TTF_OpenFont(cheminfont,taille);
	 if ( font ==NULL) {
	 	printf("ERROR LOADING FONT\n");
	 }
	 txtsurf=TTF_RenderText_Solid(font,text,txtcolor);
	 if (txtsurf==NULL) {
	 	printf("ERROR LOADING TEXT\n");
	 }
	 
	 SDL_BlitSurface(txtsurf,NULL,ecran,&postxtEcran);
	 
	
}

#include <stdio.h>
#include <stdlib.h>

char *lireMeilleurScore() {
    // Ouvrir le fichier score.txt en mode lecture
    FILE *fichier = fopen("score.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier score.txt\n");
        return NULL;
    }

    // Lire le meilleur score à partir du fichier
    int meilleurScore;
    fscanf(fichier, "%d", &meilleurScore);

    // Fermer le fichier
    fclose(fichier);

    // Allouer de la mémoire pour stocker le score sous forme de chaîne de caractères
    char *scoreStr = (char *)malloc(50 * sizeof(char));
    if (scoreStr == NULL) {
        printf("Erreur lors de l'allocation de mémoire\n");
        return NULL;
    }

    // Convertir le meilleur score en chaîne de caractères
    sprintf(scoreStr, "%d", meilleurScore);

    return scoreStr;
}

