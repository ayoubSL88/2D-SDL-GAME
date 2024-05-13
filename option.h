#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>




int initSDL();
int loadMedia();
void closeSDL();
void playBackgroundMusic();
void setWindowedMode(int windowWidth, int windowHeight);
void setFullscreenMode();
void displayOptionsMenu();

#endif /* OPTIONS_MENU_H */

    
