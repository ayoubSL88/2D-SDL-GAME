/*
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
    // Initialization
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
    if (screen == NULL) {
        fprintf(stderr, "Failed to set up screen: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf initialization failed: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    minimap map;
    initmap(&map);

    TTF_Font *police = TTF_OpenFont("pepsi.ttf", 24);
    if (police == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    // Load images for player selection
    SDL_Surface *pl_select = IMG_Load("pl_select.png");
    SDL_Surface *pl2_checked = IMG_Load("pl2_checked.png");

    // Initialize player 1
    Personne player1;
    initPerso(&player1);

    // Initialize player 2
    Personne player2;
    initPerso2(&player2);
    int player2Initialized = 0; // Flag to check if player 2 is initialized

    // Initialize enemy
    Enemy ennemi;
    ennemi = InitEnemy(ennemi, 100, 200);

    SDL_Rect pl2_checked_position;
    pl2_checked_position.x = 500; // Adjust the x-coordinate as needed
    pl2_checked_position.y = 400; // Adjust the y-coordinate as needed

    // Initialize game variables
    int quit = 0;
    int multiplayer = 0; // 0 for solo, 1 for multiplayer
    int renderPlayer2 = 0; // Flag to render player 2

    // Main game loop
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        case SDLK_RIGHT:
                            player1.direction = 0;
                            player1.vitesse = 5;
                            break;
                        case SDLK_LEFT:
                            player1.direction = 1;
                            player1.vitesse = 5;
                            break;
                        case SDLK_UP:
                            saut(&player1);
                            break;
                        case SDLK_o:
                            player1.vitesse = 15;
                            break;
			// Add controls for player 2 if multiplayer is enabled
                        case SDLK_d:
                            if (multiplayer) {
                                player2.direction = 0;
                                player2.vitesse = 5;
                            }
                            break;
                        case SDLK_q:
                            if (multiplayer) {
                                player2.direction = 1;
                                player2.vitesse = 5;
                            }
                            break;
                        case SDLK_SPACE:
                            if (multiplayer) {
                                saut(&player2);
                            }
                        case SDLK_LSHIFT:
                            player2.vitesse = 15;
                            break;
                        case SDLK_m:
                            if (!multiplayer) {
                                multiplayer = 1; // Enable multiplayer
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT:
                        case SDLK_LEFT:
                            player1.vitesse = 0;
                            break;
                        default:
                            break;
                    }
                    break;
               case SDL_MOUSEBUTTONDOWN:
		    if (multiplayer && !renderPlayer2) {
			// Check if the mouse click is within the bounds of pl2_checked
			if (event.button.x >= pl2_checked_position.x &&
			    event.button.x <= pl2_checked_position.x + pl2_checked->w &&
			    event.button.y >= pl2_checked_position.y &&
			    event.button.y <= pl2_checked_position.y + pl2_checked->h) {
				// Set flag to render player 2
				renderPlayer2 = 1;
			    }
		    }
		    break;

                default:
                    break;
            }
        }

        // Update player 1
        deplacerPerso(&player1, 1);
        animerPerso(&player1);

        // Update enemy
        ennemi = AnimateEnemy(ennemi, 0);
        int stat = 0;
        ennemi = MoveEnemy(ennemi, (SDL_Rect){player1.position.x, player1.position.y, 0, 0}, &stat, 0);

        // Clear screen
        SDL_FillRect(screen, NULL, 0x000000);

        // Render minimap
        afficherminimap(map, screen, player1.position);

        // Render player 1
        afficherPerso(player1, screen);

	if (multiplayer && renderPlayer2) {
	    deplacerPerso2(&player2, 1);
	    animerPerso(&player2);
	    afficherPerso(player2, screen);
        } else if (multiplayer) { // Render player selection screen with pl_select image
            SDL_BlitSurface(pl_select, NULL, screen, NULL);
            SDL_BlitSurface(pl2_checked, NULL, screen, &pl2_checked_position);
        }

        // Render enemy
        AfficherEnemy(ennemi, screen);

        // Render other game elements (timer, score, etc.)

        // Update screen
        SDL_Flip(screen);

        // Add delay
        SDL_Delay(80);
    }

    // Free resources
    SDL_FreeSurface(screen);
    SDL_FreeSurface(pl_select);
    SDL_FreeSurface(pl2_checked);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
*/

//*************************************************************************************************************************************

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
#define BACKGROUND_WIDTH 6523

SDL_Surface *screen = NULL;

int main(int argc, char *argv[]) {
    // Initialization
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
    if (screen == NULL) {
        fprintf(stderr, "Failed to set up screen: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf initialization failed: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    minimap map;
    initmap(&map);

    TTF_Font *police = TTF_OpenFont("pepsi.ttf", 24);
    if (police == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    // Load images for player selection
    SDL_Surface *pl_select = IMG_Load("pl_select.png");
    SDL_Surface *pl2_checked = IMG_Load("pl2_checked.png");

    // Load background image
    SDL_Surface *background = IMG_Load("bglvl1.png");
    if (background == NULL) {
        fprintf(stderr, "Failed to load background image: %s\n", IMG_GetError());
        return EXIT_FAILURE;
    }

    // Initialize player 1
    Personne player1;
    initPerso(&player1);

    // Initialize player 2
    Personne player2;
    initPerso2(&player2);
    int player2Initialized = 0; // Flag to check if player 2 is initialized

    // Initialize enemy
    Enemy ennemi;
    ennemi = InitEnemy(ennemi, 100, 200);

    SDL_Rect pl2_checked_position;
    pl2_checked_position.x = 500; // Adjust the x-coordinate as needed
    pl2_checked_position.y = 400; // Adjust the y-coordinate as needed

    // Initialize game variables
    int quit = 0;
    int multiplayer = 0; // 0 for solo, 1 for multiplayer
    int renderPlayer2 = 0; // Flag to render player 2

    // Background scrolling variables
    int bgScrollSpeed = 5;
    int bgOffsetX = 0;
    int prevPlayerX = player1.position.x;

    // Main game loop
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        case SDLK_RIGHT:
                            player1.direction = 0;
                            player1.vitesse = 5;
                            break;
                        case SDLK_LEFT:
                            player1.direction = 1;
                            player1.vitesse = 5;
                            break;
                        case SDLK_UP:
                            saut(&player1);
                            break;
                        case SDLK_o:
                            player1.vitesse = 15;
                            break;
			// Add controls for player 2 if multiplayer is enabled
                        case SDLK_d:
                            if (multiplayer) {
                                player2.direction = 0;
                                player2.vitesse = 5;
                            }
                            break;
                        case SDLK_q:
                            if (multiplayer) {
                                player2.direction = 1;
                                player2.vitesse = 5;
                            }
                            break;
                        case SDLK_SPACE:
                            if (multiplayer) {
                                saut(&player2);
                            }
                        case SDLK_LSHIFT:
                            player2.vitesse = 15;
                            break;
                        case SDLK_m:
                            if (!multiplayer) {
                                multiplayer = 1; // Enable multiplayer
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT:
                        case SDLK_LEFT:
                            player1.vitesse = 0;
                            break;
                        default:
                            break;
                    }
                    break;
               case SDL_MOUSEBUTTONDOWN:
		    if (multiplayer && !renderPlayer2) {
			// Check if the mouse click is within the bounds of pl2_checked
			if (event.button.x >= pl2_checked_position.x &&
			    event.button.x <= pl2_checked_position.x + pl2_checked->w &&
			    event.button.y >= pl2_checked_position.y &&
			    event.button.y <= pl2_checked_position.y + pl2_checked->h) {
				// Set flag to render player 2
				renderPlayer2 = 1;
			    }
		    }
		    break;

                default:
                    break;
            }
        }


        // Update player 1
        deplacerPerso(&player1, 1);
        animerPerso(&player1);

        // Update enemy
        ennemi = AnimateEnemy(ennemi, 0);
        int stat = 0;
        ennemi = MoveEnemy(ennemi, (SDL_Rect){player1.position.x, player1.position.y, 0, 0}, &stat, 0);

        // Check if player stops moving
        if (player1.direction == 1) {
            bgScrollSpeed = 0;
        } else {
            bgScrollSpeed = 5;
        }

        // Check if player reaches the middle of the screen
        if (player1.position.x >= SCREEN_WIDTH / 2) {
            // Scroll background
            bgOffsetX += bgScrollSpeed;
            if (bgOffsetX >= BACKGROUND_WIDTH) {
                bgOffsetX = 0;
            }
        }

        // Update previous player position
        prevPlayerX = player1.position.x;

        // Clear screen
        SDL_FillRect(screen, NULL, 0x000000);

        // Render background
        SDL_Rect bgSrcRect = {bgOffsetX, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect bgDestRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_BlitSurface(background, &bgSrcRect, screen, &bgDestRect);

        // Render minimap
        afficherminimap(map, screen, player1.position);

        // Render player 1
        afficherPerso(player1, screen);

        // Render player 2 if multiplayer is enabled and player 2 is selected
        if (multiplayer && renderPlayer2) {
            deplacerPerso2(&player2, 1);
            animerPerso(&player2);
            afficherPerso(player2, screen);
        } else if (multiplayer) { // Render player selection screen with pl_select image
            SDL_BlitSurface(pl_select, NULL, screen, NULL);
            SDL_BlitSurface(pl2_checked, NULL, screen, &pl2_checked_position);
        }

        // Render enemy
        AfficherEnemy(ennemi, screen);

        // Render other game elements (timer, score, etc.)

        // Update screen
        SDL_Flip(screen);

        // Add delay
        SDL_Delay(80);
    }

    // Free resources
    SDL_FreeSurface(screen);
    SDL_FreeSurface(pl_select);
    SDL_FreeSurface(pl2_checked);
    SDL_FreeSurface(background);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}



