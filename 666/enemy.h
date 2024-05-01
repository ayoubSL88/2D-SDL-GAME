#ifndef ENEMY_H
#define ENEMY_H

#include <SDL/SDL.h>
#include "Personne.h" // Inclure le fichier personne.h

typedef struct {
    SDL_Surface *image[3];
    SDL_Surface *image2[3];
    SDL_Surface *Hit;
    SDL_Surface *imageActuel;
    SDL_Rect position;
    SDL_Rect positionO;
    int frame;
    int direction;
    int died;
} Enemy;

typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    int collected;
} Bonus;

Enemy InitEnemy(Enemy Ennemie, int x, int y);
void AfficherEnemy(Enemy Ennemie, SDL_Surface *screen);
Enemy AnimateEnemy(Enemy Ennemie, int stat);
Enemy MoveEnemy(Enemy Ennemie, SDL_Rect personnage, int *stat, int mouvement);

Bonus initBonus(Bonus bonus, int x, int y);
void AfficherBonus(Bonus bonus, SDL_Surface *screen);
int collisionBonus(Personne *p, Bonus *bonus); // Utilisation de Personne ici
void collecterBonus(Personne *p, Bonus *bonus); // Utilisation de Personne ici

#endif

