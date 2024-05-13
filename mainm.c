#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "functions.h"
#include "option.h"
#define LARGEUR_ECRAN 1920
#define HAUTEUR_ECRAN 1080
#define LARGEUR_IMAGE_BACKGROUND 6530
#define LARGEUR_JOUEUR 50
#define HAUTEUR_JOUEUR 50
#define VITESSE_JOUEUR_X 13
#define VITESSE_JOUEUR_Y 13
#define VITESSE_DEFILEMENT_X 5
#define VITESSE_DEFILEMENT_Y 5
#define VITESSE_SAUT 200
#define GRAVITE 10
#define ZOOM_FACTOR 2
// États du programme
typedef enum {
    MENU,
    OPTIONS,
    GAME
} ProgramState;

int main() {
    // VARIABLES LOCALES
    SDL_Event event;
    ProgramState state = MENU; // État initial du programme
    bool gameloop = true;
    SDL_Surface *ecran = NULL, *imgmenu = NULL, *lvlback = NULL;
    SDL_Surface *play1 = NULL, *play2 = NULL, *rank1 = NULL, *rank2 = NULL, *op1 = NULL, *op2 = NULL, *exit1 = NULL, *exit2 = NULL;
    Mix_Music *musicmenu = NULL, *sonbref = NULL;
    SDL_Rect posimg, poslvl1;
    SDL_Rect play, rank, op, exit;

    // INITIALISATION ET CREATION DU FENETRE + AFFICHAGE D'IMAGE MENU + Chargement de music
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("ERROR INITIALIZING SDL\n");
        SDL_Quit();
        return 1;
    }

    ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) {
        printf("ERROR CREATING WINDOW");
        SDL_Quit();
        return 1;
    }

    if (!initSDL()) { // Call the initSDL function from option.c
        printf("ERROR INITIALIZING SDL\n");
        SDL_Quit();
        return 1;
    }

    if (!loadMedia()) { // Call the loadMedia function from option.c
        printf("ERROR LOADING MEDIA\n");
        SDL_Quit();
        return 1;
    }

    // Charger les boutons du menu principal
    loadbtns(&play1, &play2, &rank1, &rank2, &op1, &op2, &exit1, &exit2);

    imgmenu = IMG_Load("menu.png");
    if (imgmenu == NULL) {
        printf("ERROR OPENING MENU IMAGE");
        SDL_FreeSurface(ecran);
        SDL_Quit();
        return 1;
    } else {
        posimg.x = 0;
        posimg.y = 0;
        posimg.h = imgmenu->h;
        posimg.w = imgmenu->w;
        dimenstionsBTN(&play, &rank, &op, &exit, play1);
    }

    // Initialiser et jouer la musique du menu
    Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096);
    musicmenu = Mix_LoadMUS("projet v1.mp3");
    if (musicmenu == NULL) {
        printf("ERROR OPENING MUSIC \n");
    }
        // Blit  D'image menu + boutons
    SDL_BlitSurface(imgmenu, NULL, ecran, &posimg);
    musicmenu = Mix_LoadMUS("projet v1.mp3");

    Mix_PlayMusic(musicmenu, -1);

    while (gameloop) {
        // Gestion des événements
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            printf("EXITING...\n");
                            gameloop = false;
                            break;
                        case SDLK_h:
                            printf("HELP REQUESTED\n");
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (state == MENU) {
                        changetexture(play, rank, op, exit, event, play1, play2, rank1, rank2, op1, op2, exit1, exit2, ecran);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (state == MENU) {
                            if (sourisSurbtn(play, event)) {
                                state = GAME;
    int continuer = 1;
    int gauchePresse = 0, droitePresse = 0, hautPresse = 0, basPresse = 0, espacePresse = 0;
    int aPresse = 0, dPresse = 0, wPresse = 0, sPresse = 0;
    int saut = 0;
    Camera camera;
    int frame = 0;
    int score = 0;

    Joueur joueur1;
    Joueur joueur2;
    Background background;
    Enemy enemy;
    enemy.state = Waiting;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    screen = SDL_SetVideoMode(LARGEUR_ECRAN * 2, HAUTEUR_ECRAN, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    loadSunImages();

    initialiserJoueur(&joueur1, "joueur1.png", 10, 100);
    initialiserJoueur(&joueur2, "joueur2.png", 10 + LARGEUR_ECRAN, 100);
    initialiserBackground(&background, "bg1.png");

    initCamera(&camera);

    Uint32 startTime = SDL_GetTicks();
    Uint32 lastTime = startTime;

    while (continuer) {
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
                            background.scrollX1 += VITESSE_DEFILEMENT_X;
                            break;
                        case SDLK_h: // High Scores button
                            displayHighScores();
                            break;
                        case SDLK_p: // Save score and display last score
                            saveScore(score);
                            {
                                SDL_Surface *scoreScreen = loadImage("score_screen.png");
                                SDL_BlitSurface(scoreScreen, NULL, screen, NULL);
                                SDL_Flip(screen);
                                SDL_Delay(3000); // Attendre 3 secondes
                                SDL_FreeSurface(scoreScreen); // Libérer la surface de l'écran de score
                            }
                            printf("Last Score: %d\n", readLastScore());
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

        if (espacePresse && !saut) {
            saut = 1;
            joueur1.y -= VITESSE_SAUT;
        }

        if (wPresse && !saut) {
            saut = 1;
            joueur2.y -= VITESSE_SAUT;
        }

        if (gauchePresse) {
            joueur1.x -= VITESSE_JOUEUR_X;
            if (joueur1.x < 0) {
                joueur1.x = 0;
            }
            background.scrollX1 += VITESSE_DEFILEMENT_X;
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

        if (aPresse) {
            joueur2.x -= VITESSE_JOUEUR_X;
            if (joueur2.x < LARGEUR_ECRAN + background.scrollX2) {
                joueur2.x = LARGEUR_ECRAN + background.scrollX2;
            }
            background.scrollX2 += VITESSE_DEFILEMENT_X; // Défilement dans le sens inverse du joueur 2
        }
        if (dPresse) {
            joueur2.x += VITESSE_JOUEUR_X;
            if (joueur2.x > 2 * LARGEUR_ECRAN - joueur2.sprite->w + background.scrollX2) {
                joueur2.x = 2 * LARGEUR_ECRAN - joueur2.sprite->w + background.scrollX2;
            }
            background.scrollX2 -= VITESSE_DEFILEMENT_X;
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

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); // Blanc

        afficherBackground(&background, 1);
        afficherBackground(&background, 2);

        afficherJoueur(&joueur1);
        afficherJoueur(&joueur2);

        animerBack(&frame);

        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - lastTime;
        if (elapsedTime >= 1000) { // Une seconde écoulée
            score += 10; // Incrémenter le score
            lastTime = currentTime;
        }

        afficherScore(score, screen);

        SDL_Flip(screen);
    }

    SDL_FreeSurface(joueur1.sprite);
    SDL_FreeSurface(joueur2.sprite);
    SDL_FreeSurface(background.image);
    TTF_Quit();
    SDL_Quit();
                                printf("TEST SUR CLICK PASSE\n");
   } else if (sourisSurbtn(rank, event)) { 
if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Chargement de l'image
    SDL_Surface *image = IMG_Load("score_screen.png");
    if (image == NULL) {
        printf("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre
    SDL_Surface *ecran = SDL_SetVideoMode(1920, 1024, 32, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        SDL_Quit();
        return 1;
    }

    // Chargement de la police
    TTF_Font *police = TTF_OpenFont("arial.ttf", 50);
    if (police == NULL) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        SDL_FreeSurface(image);
        SDL_Quit();
        return 1;
    }

    // Couleur du texte
    SDL_Color couleur = {255, 255, 255}; // Blanc

    lire_scores_et_trouver_max("score.txt", "rank1.txt");

    const char* texte = lire_ligne("rank1.txt");
    remove("rank1.txt");

    // Création de la surface de texte
    SDL_Surface *texteSurface = TTF_RenderText_Blended(police, texte, couleur);
    if (texteSurface == NULL) {
        printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        TTF_CloseFont(police);
        SDL_FreeSurface(image);
        SDL_Quit();
        return 1;
    }
    SDL_Rect posTexte;
    posTexte.x = image->w + 10; // 10 pixels à droite de l'image
    posTexte.y = (ecran->h - texteSurface->h) / 2; // Centré verticalement

SDL_BlitSurface(image, NULL, ecran, NULL);

SDL_Flip(ecran);

SDL_Delay(2000);
loadtext1(texte, "arial.ttf", 100, 0,800, 540, ecran);
SDL_Delay(1000);



// Mise à jour de la fenêtre
SDL_Flip(ecran);

    // Libération de la mémoire
    SDL_FreeSurface(image);
    SDL_FreeSurface(texteSurface);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();


                                printf("rank\n");
                            } else if (sourisSurbtn(op, event)) {
                                printf("Options\n");
                                state = OPTIONS; // Passer à l'état des options
                            } else if (sourisSurbtn(exit, event)) {
                                printf("Quit\n");
                                gameloop = false;
                            }
                        } else if (state == OPTIONS) {
                            // Gérer les clics dans la fenêtre des options (option.c)
                            displayOptionsMenu();
                            state = MENU; // Revenir à l'état du menu principal après avoir fermé la fenêtre des options
                        }
                    }
                    break;
            }
        }

        // Mise à jour de l'affichage
        SDL_Flip(ecran); // Mettre à jour l'écran

        // Autres logiques et rendu du jeu...
    }

    // Libérer les ressources
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(imgmenu);
    SDL_FreeSurface(play1);
    SDL_FreeSurface(play2);
    SDL_FreeSurface(rank1);
    SDL_FreeSurface(rank2);
    SDL_FreeSurface(op1);
    SDL_FreeSurface(op2);
    SDL_FreeSurface(exit1);
    SDL_FreeSurface(exit2);
    SDL_FreeSurface(lvlback);

    Mix_FreeMusic(musicmenu);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}

