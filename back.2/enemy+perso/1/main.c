#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Personne.h"
#include "enemy.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

SDL_Surface *screen = NULL;

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Impossible d'initialiser SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
    if (screen == NULL) {
        fprintf(stderr, "Impossible de créer la fenêtre: %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation du personnage
    Personne player;
    initPerso(&player);

    // Initialisation de l'ennemi
    Enemy ennemi;
    ennemi = InitEnemy(ennemi, 100, 200);

     // Main loop
    int quit = 0;
    while (!quit)
    {
        // Event handling
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = 1;
                    break;
                case SDLK_RIGHT:
                    player.direction = 0;
                    player.vitesse = 5; // Adjust the speed as needed
                    break;
                case SDLK_LEFT:
                    player.direction = 1;
                    player.vitesse = 5; // Adjust the speed as needed
                    break;
                case SDLK_UP:
                    saut(&player);
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                case SDLK_LEFT:
                    player.vitesse = 0;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        // Mouvement et animation du personnage
        deplacerPerso(&player, 1);
        animerPerso(&player);

        // Animation de l'ennemi
        ennemi = AnimateEnemy(ennemi, 0);

        // Déplacement de l'ennemi
        int stat = 0;
        ennemi = MoveEnemy(ennemi, (SDL_Rect){player.position.x, player.position.y, 0, 0}, &stat, 0);

        // Effacement de l'écran
        SDL_FillRect(screen, NULL, 0x000000);

        // Affichage du personnage
        afficherPerso(player, screen);

        // Affichage de l'ennemi
        AfficherEnemy(ennemi, screen);

        // Mise à jour de l'écran
        SDL_Flip(screen);

        // Pause pour contrôler la fréquence de rafraîchissement
        SDL_Delay(30);
    }

    // Libération des ressources
    SDL_Quit();
    return 0;
}

