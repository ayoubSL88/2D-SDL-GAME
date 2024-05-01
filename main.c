#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"
#include "Personne.h"
#include "enemy.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MINIMAP_WIDTH 500
#define MINIMAP_HEIGHT 30

SDL_Surface *screen = NULL;

int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
    if(screen == NULL) {
        fprintf(stderr, "Failed to set up screen: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    if(TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf initialization failed: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }
    minimap map;
    initmap(&map);

    TTF_Font *police = TTF_OpenFont("pepsi.ttf", 24);
    if(police == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    Personne player;
    initPerso(&player);

    Enemy ennemi;
    ennemi = InitEnemy(ennemi, 100, 200);

    int quit = 0;
    while(!quit) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        case SDLK_RIGHT:
                            player.direction = 0;
                            player.vitesse = 5;
                            break;
                        case SDLK_LEFT:
                            player.direction = 1;
                            player.vitesse = 5;
                            break;
                        case SDLK_UP:
                            saut(&player);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym) {
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

        deplacerPerso(&player, 1);
        animerPerso(&player);

        ennemi = AnimateEnemy(ennemi, 0);
        int stat = 0;
        ennemi = MoveEnemy(ennemi, (SDL_Rect){player.position.x, player.position.y, 0, 0}, &stat, 0);

        SDL_FillRect(screen, NULL, 0x000000);

       afficherminimap(map, screen, player.position);

        afficherPerso(player, screen);

        AfficherEnemy(ennemi, screen);

        Uint32 temps = 0;
        affichertemp(&temps, screen, police);

        SDL_Flip(screen);

        SDL_Delay(30);
    }

    SDL_FreeSurface(screen);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

