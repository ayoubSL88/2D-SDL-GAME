#ifndef ENEMY_H
#define ENEMY_H

#include <SDL/SDL.h>

typedef struct {
    SDL_Surface *image[3]; // Tableau de surfaces pour les sprites de l'ennemi
    SDL_Surface *image2[3]; // Tableau de surfaces pour les sprites de l'ennemi dans l'autre direction
    SDL_Surface *Hit; // Surface pour l'image de l'ennemi touché
    SDL_Surface *imageActuel; // Surface pour l'image actuelle de l'ennemi
    SDL_Rect position; // Position de l'ennemi
    SDL_Rect positionO; // Position originale de l'ennemi
    int frame; // Frame actuelle de l'animation
    int direction; // Direction de l'ennemi (0 ou 1)
    int died; // Flag indiquant si l'ennemi est mort
} Enemy;

// Initialise un ennemi avec ses images et sa position
Enemy InitEnemy(Enemy Ennemie, int x, int y);

// Affiche un ennemi sur l'écran
void AfficherEnemy(Enemy Ennemie, SDL_Surface *screen);

// Anime un ennemi en fonction de son état
Enemy AnimateEnemy(Enemy Ennemie, int stat);

// Déplace un ennemi en fonction de la position du personnage et de son état
Enemy MoveEnemy(Enemy Ennemie, SDL_Rect personnage, int *stat, int mouvement);

// Marque un ennemi comme mort
Enemy diedennemie(Enemy Ennemie, int coe);

#endif

