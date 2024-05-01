#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


typedef struct {
    
SDL_Rect camera_pos_x;
SDL_Rect camera_pos_y; // Position de la caméra
    int direction; // Direction de scrolling (0: aucune, 1: droite, 2: gauche, 3: haut, 4: bas)
} Background;

void afficherBackground(SDL_Surface* ecran, SDL_Surface* image);

void initBackground(Background *bg, int LargeurFenetre, int HauteurFenetre, int Ecran) ;
void scrolling(Background *bg, int direction, int dx, int dy, int hauteurEcran);

void animerBack(Camera *camera, int *frame);
