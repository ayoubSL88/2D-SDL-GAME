#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define ASPECT_RATIO_WIDTH 16
#define ASPECT_RATIO_HEIGHT 9

SDL_Surface* screen1 = NULL;
SDL_Surface* optionsBackground = NULL;
SDL_Surface* increaseButtonDefault = NULL;
SDL_Surface* increaseButtonHover = NULL;
SDL_Surface* decreaseButtonDefault = NULL;
SDL_Surface* decreaseButtonHover = NULL;
SDL_Surface* volumeImages[6]; // Array to store volume images
SDL_Surface* fullscreenButtonDefault = NULL;
SDL_Surface* fullscreenButtonHover = NULL;
SDL_Surface* windowedButtonDefault = NULL;
SDL_Surface* windowedButtonHover = NULL;
SDL_Surface* closeButtonDefault = NULL;
SDL_Surface* closeButtonHover = NULL;
Mix_Music* backgroundMusic = NULL;

int soundLevel = 3; // Initial sound level (0-5)

int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 0;
    }

    screen1 = SDL_SetVideoMode(1920, 1080, 32, SDL_SWSURFACE);
    if (screen1== NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur lors de l'initialisation de SDL_mixer : %s\n", Mix_GetError());
        return 0;
    }

    return 1;
}

int loadMedia() {
    backgroundMusic = Mix_LoadMUS("music.mp3");
    if (backgroundMusic == NULL) {
        printf("Erreur lors du chargement de la musique de fond : %s\n", Mix_GetError());
        return 0;
    }

    optionsBackground = IMG_Load("opt_bg.png"); 
    increaseButtonDefault = IMG_Load("up1.png");
    increaseButtonHover = IMG_Load("up2.png");
    decreaseButtonDefault = IMG_Load("down1.png");
    decreaseButtonHover = IMG_Load("down2.png");
    fullscreenButtonDefault = IMG_Load("fullscreen1.png");
    fullscreenButtonHover = IMG_Load("fullscreen2.png");
    windowedButtonDefault = IMG_Load("windowed1.png");
    windowedButtonHover = IMG_Load("windowed2.png");
    closeButtonDefault = IMG_Load("exit1.png");
    closeButtonHover = IMG_Load("exit2.png");

    for (int i = 0; i < 6; ++i) {
        char filename[20];
        sprintf(filename, "s%d.png", i); 
        volumeImages[i] = IMG_Load(filename);
        if (volumeImages[i] == NULL) {
            printf("Erreur lors du chargement de l'image de volume %d : %s\n", i, IMG_GetError());
            return 0;
        }
    }

    if (optionsBackground == NULL || increaseButtonDefault == NULL || increaseButtonHover == NULL ||
        decreaseButtonDefault == NULL || decreaseButtonHover == NULL ||
        fullscreenButtonDefault == NULL || fullscreenButtonHover == NULL ||
        windowedButtonDefault == NULL || windowedButtonHover == NULL ||
        closeButtonDefault == NULL || closeButtonHover == NULL) {
        printf("Erreur lors du chargement des ressources : %s\n", IMG_GetError());
        return 0;
    }

    return 1;
}

void closeSDL() {
    SDL_FreeSurface(optionsBackground);
    SDL_FreeSurface(increaseButtonDefault);
    SDL_FreeSurface(increaseButtonHover);
    SDL_FreeSurface(decreaseButtonDefault);
    SDL_FreeSurface(decreaseButtonHover);
    SDL_FreeSurface(fullscreenButtonDefault);
    SDL_FreeSurface(fullscreenButtonHover);
    SDL_FreeSurface(windowedButtonDefault);
    SDL_FreeSurface(windowedButtonHover);
    SDL_FreeSurface(closeButtonDefault);
    SDL_FreeSurface(closeButtonHover);

    Mix_FreeMusic(backgroundMusic);

    for (int i = 0; i < 6; ++i) {
        SDL_FreeSurface(volumeImages[i]);
    }

    Mix_CloseAudio();

    SDL_Quit();
}

void playBackgroundMusic() {
    Mix_PlayMusic(backgroundMusic, -1);
}

void setWindowedMode(int windowWidth) {
    int windowHeight = windowWidth * ASPECT_RATIO_HEIGHT / ASPECT_RATIO_WIDTH;
    SDL_Surface* newWindow = SDL_SetVideoMode(windowWidth, windowHeight, 32, SDL_SWSURFACE | SDL_RESIZABLE);
    if (newWindow != NULL) {
        screen1 = newWindow; // Update the screen surface to the new window
    } else {
        fprintf(stderr, "Unable to switch to windowed mode: %s\n", SDL_GetError());
    }
}

void displayOptionsMenu() {
    int quit = 0;
    int mouseX;
    int mouseY;
    SDL_Event event;

    // Define flags for button hover state
    int increaseButtonHovered = 0;
    int decreaseButtonHovered = 0;
    int fullscreenButtonHovered = 0;
    int windowedButtonHovered = 0;
    int closeButtonHovered = 0;

    // Define rectangles for all buttons
    SDL_Rect increaseButtonRect = {620, 350, increaseButtonDefault->w, increaseButtonDefault->h};
    SDL_Rect decreaseButtonRect = {230, 350, decreaseButtonDefault->w, decreaseButtonDefault->h};
    SDL_Rect volumeRect = {220, 200, volumeImages[soundLevel]->w, volumeImages[soundLevel]->h};
    SDL_Rect fullscreenButtonRect = {790, 200, fullscreenButtonDefault->w, fullscreenButtonDefault->h};
    SDL_Rect windowedButtonRect = {790, 400, windowedButtonDefault->w, windowedButtonDefault->h};
    SDL_Rect closeButtonRect = {1560, 7, closeButtonDefault->w, closeButtonDefault->h};

    while (!quit) {
        // Event handling loop
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;  // Set quit flag
                    break;
                case SDL_MOUSEMOTION:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;

                    // Check for mouse hover over buttons and set hover flags
                    increaseButtonHovered = (mouseX >= increaseButtonRect.x && mouseX <= increaseButtonRect.x + increaseButtonRect.w &&
                                            mouseY >= increaseButtonRect.y && mouseY <= increaseButtonRect.y + increaseButtonRect.h);
                    decreaseButtonHovered = (mouseX >= decreaseButtonRect.x && mouseX <= decreaseButtonRect.x + decreaseButtonRect.w &&
                                            mouseY >= decreaseButtonRect.y && mouseY <= decreaseButtonRect.y + decreaseButtonRect.h);
                    fullscreenButtonHovered = (mouseX >= fullscreenButtonRect.x && mouseX <= fullscreenButtonRect.x + fullscreenButtonRect.w &&
                                            mouseY >= fullscreenButtonRect.y && mouseY <= fullscreenButtonRect.y + fullscreenButtonRect.h);
                    windowedButtonHovered = (mouseX >= windowedButtonRect.x && mouseX <= windowedButtonRect.x + windowedButtonRect.w &&
                                            mouseY >= windowedButtonRect.y && mouseY <= windowedButtonRect.y + windowedButtonRect.h);
                    closeButtonHovered = (mouseX >= closeButtonRect.x && mouseX <= closeButtonRect.x + closeButtonRect.w &&
                                            mouseY >= closeButtonRect.y && mouseY <= closeButtonRect.y + closeButtonRect.h);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseX = event.button.x;
                    mouseY = event.button.y;

                    // Check for clicks on each button
                    if (mouseX >= increaseButtonRect.x && mouseX <= increaseButtonRect.x + increaseButtonRect.w &&
                        mouseY >= increaseButtonRect.y && mouseY <= increaseButtonRect.y + increaseButtonRect.h) {
                        // Increase sound level
                        if (soundLevel < 5) {
                            soundLevel++;
                            Mix_VolumeMusic(soundLevel * MIX_MAX_VOLUME / 5);
                        }
                    } else if (mouseX >= decreaseButtonRect.x && mouseX <= decreaseButtonRect.x + decreaseButtonRect.w &&
                               mouseY >= decreaseButtonRect.y && mouseY <= decreaseButtonRect.y + decreaseButtonRect.h) {
                        // Decrease sound level
                        if (soundLevel > 0) {
                            soundLevel--;
                            Mix_VolumeMusic(soundLevel * MIX_MAX_VOLUME / 5);
                        }
                    } else if (mouseX >= fullscreenButtonRect.x && mouseX <= fullscreenButtonRect.x + fullscreenButtonRect.w &&
                               mouseY >= fullscreenButtonRect.y && mouseY <= fullscreenButtonRect.y + fullscreenButtonRect.h) {
                        // Toggle fullscreen mode
                        if (screen1->flags & SDL_FULLSCREEN) {
                            screen1 = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_RESIZABLE);
                        } else {
                            screen1= SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_FULLSCREEN);
                        }
                        if (screen1 == NULL) {
                            fprintf(stderr, "Unable to switch video mode: %s\n", SDL_GetError());
                        }
                    } else if (mouseX >= windowedButtonRect.x && mouseX <= windowedButtonRect.x + windowedButtonRect.w &&
                               mouseY >= windowedButtonRect.y && mouseY <= windowedButtonRect.y + windowedButtonRect.h) {
                        // Toggle windowed mode
                        if (screen1->flags & SDL_FULLSCREEN) {
                            screen1 = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_RESIZABLE);
                        }
                        if (screen1 == NULL) {
                            fprintf(stderr, "Unable to switch to windowed mode: %s\n", SDL_GetError());
                        }
                    } else if (mouseX >= closeButtonRect.x && mouseX <= closeButtonRect.x + closeButtonRect.w &&
                               mouseY >= closeButtonRect.y && mouseY <= closeButtonRect.y + closeButtonRect.h) {
                        // Close the options menu
                        quit = 1;
                    }
                    break;
            }
        }

        // Rendering loop
        SDL_BlitSurface(optionsBackground, NULL, screen1, NULL);
        SDL_BlitSurface(increaseButtonHovered ? increaseButtonHover : increaseButtonDefault, NULL, screen1, &increaseButtonRect);
        SDL_BlitSurface(decreaseButtonHovered ? decreaseButtonHover : decreaseButtonDefault, NULL, screen1, &decreaseButtonRect);
        SDL_BlitSurface(volumeImages[soundLevel], NULL, screen1, &volumeRect);
        SDL_BlitSurface(fullscreenButtonHovered ? fullscreenButtonHover : fullscreenButtonDefault, NULL, screen1, &fullscreenButtonRect);
        SDL_BlitSurface(windowedButtonHovered ? windowedButtonHover : windowedButtonDefault, NULL, screen1, &windowedButtonRect);
        SDL_BlitSurface(closeButtonHovered ? closeButtonHover : closeButtonDefault, NULL, screen1, &closeButtonRect);
        SDL_Flip(screen1);
    }

    // Quit SDL and free resources
    closeSDL();
}


