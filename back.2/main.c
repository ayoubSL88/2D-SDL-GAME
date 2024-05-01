#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Pour usleep
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define LARGEUR_ECRAN 700 // Largeur de chaque moitié de l'écran
#define HAUTEUR_ECRAN 700
#define LARGEUR_IMAGE_BACKGROUND 3192
#define LARGEUR_JOUEUR 50
#define HAUTEUR_JOUEUR 50
#define VITESSE_JOUEUR_X 13
#define VITESSE_JOUEUR_Y 13
#define VITESSE_DEFILEMENT_X 5
#define VITESSE_DEFILEMENT_Y 5
#define VITESSE_SAUT 200
#define GRAVITE 10
#define ZOOM_FACTOR 2 // Facteur de zoom

typedef struct {
    int x, y, w, h;
} Camera;

typedef struct {
    int x, y;
    SDL_Surface *sprite;
} Joueur;

typedef struct {
    SDL_Rect posBack1;
    SDL_Rect posBack2;
    SDL_Rect posEcran;
    int scrollX1;
    int scrollX2;
    SDL_Surface *image;
} Background;

typedef enum {
    Waiting,
    Following,
    Attacking
} EnemyState;

typedef struct {
    EnemyState state;
    // Autres attributs de l'ennemi
} Enemy;

SDL_Surface *screen = NULL;
SDL_Surface *elements = NULL;
SDL_Surface *sunImages[4];
SDL_Rect sunPos;

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
    background->image = IMG_Load(imagePath);
    if (!background->image) {
        fprintf(stderr, "Failed to load background image: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }
    
    // Initialisation des positions et scrolling
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

// Fonction pour simuler le calcul de la distance entre l'ennemi et le héros
int calculateDistance() {
    // Simulation d'une distance aléatoire entre 0 et 700 pour cet exemple
    return rand() % 701;
}

void updateEnemyState(Enemy *enemy, int distance) {
    switch(enemy->state) {
        case Waiting:
            if (distance <= 600 && distance > 100) {
                enemy->state = Following;
            }
            break;
        case Following:
            if (distance <= 100) {
                enemy->state = Attacking;
            } else if (distance > 600) {
                enemy->state = Waiting;
            }
            break;
        case Attacking:
            if (distance > 100) {
                enemy->state = Following;
            }
            break;
        default:
            break;
    }
}

int main() {
    int continuer = 1;
    int gauchePresse = 0, droitePresse = 0, hautPresse = 0, basPresse = 0, espacePresse = 0;
    int aPresse = 0, dPresse = 0, wPresse = 0, sPresse = 0;
    int saut = 0;
    Camera camera;
    int frame = 0;

    Joueur joueur1;
    Joueur joueur2;
    Background background;
    Enemy enemy;
    enemy.state = Waiting;

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    screen = SDL_SetVideoMode(LARGEUR_ECRAN * 2, HAUTEUR_ECRAN, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    loadSunImages();

    initialiserJoueur(&joueur1, "joueur1.png", 10, 100);
    initialiserJoueur(&joueur2, "joueur2.png", 10 + LARGEUR_ECRAN, 100);
    initialiserBackground(&background, "background.png");

    initCamera(&camera);

    // Boucle principale du jeu
    while (continuer) {
        // Gestion des événements
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            hautPresse = 1;
                            break;
                        case SDLK_DOWN:
                            basPresse = 1;
                            break;
                        case SDLK_LEFT:
                            gauchePresse = 1;
                            break;
                        case SDLK_RIGHT:
                            droitePresse = 1;
                            break;
                        case SDLK_SPACE:
                            espacePresse = 1;
                            break;
                        case SDLK_w:
                            wPresse = 1;
                            break;
                        case SDLK_s:
                            sPresse = 1;
                            break;
                        case SDLK_a:
                            aPresse = 1;
                            break;
                        case SDLK_d:
                            dPresse = 1;
                            // Faire défiler le background 1 vers la droite avec la même vitesse que le background 2
                            background.scrollX1 += VITESSE_DEFILEMENT_X;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            hautPresse = 0;
                            break;
                        case SDLK_DOWN:
                            basPresse = 0;
                            break;
                        case SDLK_LEFT:
                            gauchePresse = 0;
                            break;
                        case SDLK_RIGHT:
                            droitePresse = 0;
                            break;
                        case SDLK_SPACE:
                            espacePresse = 0;
                            break;
                        case SDLK_w:
                            wPresse = 0;
                            break;
                        case SDLK_s:
                            sPresse = 0;
                            break;
                        case SDLK_a:
                            aPresse = 0;
                            break;
                        case SDLK_d:
                            dPresse = 0;
                            break;
                    }
                    break;
            }
        }

        // Gestion du saut pour le premier joueur
        if (espacePresse && !saut) {
            saut = 1;
            joueur1.y -= VITESSE_SAUT;
        }

        // Gestion du saut pour le deuxième joueur
        if (wPresse && !saut) {
            saut = 1;
            joueur2.y -= VITESSE_SAUT;
        }

        // Déplacement du premier joueur et du premier background
        if (gauchePresse) {
            joueur1.x -= VITESSE_JOUEUR_X;
            if (joueur1.x < 0) {
                joueur1.x = 0;
            }
            background.scrollX1 += VITESSE_DEFILEMENT_X; // Déplacement du scrolling du premier background vers la droite
            if (background.scrollX1 >= LARGEUR_IMAGE_BACKGROUND / 2) {
                background.scrollX1 = 0;
            }
        }
        if (droitePresse) {
            joueur1.x += VITESSE_JOUEUR_X;
            if (joueur1.x > LARGEUR_ECRAN - joueur1.sprite->w) {
                joueur1.x = LARGEUR_ECRAN - joueur1.sprite->w;
            }
        }
        if (hautPresse) {
            joueur1.y -= VITESSE_JOUEUR_Y;
        }
        if (basPresse) {
            joueur1.y += VITESSE_JOUEUR_Y;
        }

        // Déplacement du deuxième joueur et du deuxième background
        if (aPresse) {
            joueur2.x -= VITESSE_JOUEUR_X;
            if (joueur2.x < LARGEUR_ECRAN + background.scrollX2) {
                joueur2.x = LARGEUR_ECRAN + background.scrollX2;
            }
            background.scrollX2 += VITESSE_DEFILEMENT_X; // Déplacement du scrolling du deuxième background vers la droite
            if (background.scrollX2 >= LARGEUR_IMAGE_BACKGROUND / 2) {
                background.scrollX2 = 0;
            }
        }
        if (dPresse) {
            joueur2.x += VITESSE_JOUEUR_X;
            if (joueur2.x > 2 * LARGEUR_ECRAN - joueur2.sprite->w + background.scrollX2) {
                joueur2.x = 2 * LARGEUR_ECRAN - joueur2.sprite->w + background.scrollX2;
            }
            background.scrollX2 -= VITESSE_DEFILEMENT_X; // Déplacement du scrolling du deuxième background vers la gauche
            if (background.scrollX2 <= -LARGEUR_IMAGE_BACKGROUND / 2 + LARGEUR_ECRAN) {
                background.scrollX2 = -LARGEUR_IMAGE_BACKGROUND / 2 + LARGEUR_ECRAN;
            }
        }
        if (wPresse) {
            joueur2.y -= VITESSE_JOUEUR_Y;
        }
        if (sPresse) {
            joueur2.y += VITESSE_JOUEUR_Y;
        }

        // Mise à jour de l'écran
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // Fond noir

        afficherBackground(&background, 1); // Affichage du premier background
        afficherBackground(&background, 2); // Affichage du deuxième background

        afficherJoueur(&joueur1); // Affichage du premier joueur
        afficherJoueur(&joueur2); // Affichage du deuxième joueur

        animerBack(&frame); // Animation du soleil

        // Simulation du calcul de la distance entre l'ennemi et le héros
        int distance = calculateDistance();

        // Mise à jour de l'état de l'ennemi en fonction de la distance
        updateEnemyState(&enemy, distance);

        // Autres actions en fonction de l'état de l'ennemi, telles que l'animation et le déplacement

        // Pause pour simuler le passage du temps dans le jeu
        usleep(100000); // 100 millisecondes

        SDL_Flip(screen); // Mise à jour de l'écran
    }

    // Libération des ressources et arrêt de SDL
    SDL_FreeSurface(joueur1.sprite);
    SDL_FreeSurface(joueur2.sprite);
    SDL_FreeSurface(background.image);
    SDL_Quit();

    return 0;
}

