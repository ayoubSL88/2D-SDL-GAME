#ifndef PERSONNE_H
#define PERSONNE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct {
    SDL_Surface *images[2][4];
    SDL_Rect position;
    int direction;
    int nbr_frame;
    double vitesse, acceleration, vitesse_saut;
    double dx;
    int ground, up;
} Personne;

typedef struct {
    SDL_Surface *vie;
    int valeur_vie;
    SDL_Rect pos_spr, pos;
} Vie;

void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface *screen);
void animerPerso(Personne *p);
void deplacerPerso(Personne *p, int dt);
void saut(Personne *p);

#endif

