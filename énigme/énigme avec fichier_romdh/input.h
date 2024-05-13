#ifndef input_H_INCLUDED
#define input_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <string.h>

typedef struct
{
    int e , Return;

} Input;

void init_input(Input *I);

#endif