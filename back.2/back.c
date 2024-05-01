#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include "back.h"

#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600
#define LARGEUR_IMAGE_BACKGROUND 1600 // Suppose une image de fond deux fois plus large que l'écran
#define LARGEUR_JOUEUR 50 // Largeur du joueur


SDL_Surface* chargerSurface(const char* palestine.png) {
    SDL_Surface* surface = SDL_LoadBMP("palestine.png");
    if (!surface) {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", SDL_GetError());
        return NULL;
    }
    return surface;
}

void afficherBackground(SDL_Surface* ecran, SDL_Surface* image) {
    // Effacer l'écran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // Fond noir

    // Dessiner l'image sur l'écran
    SDL_Rect positionimage = {10, 10, 0, 0}; // Position de l'image
    SDL_BlitSurface(image, NULL, ecran, &positionimage);


 
}




void initBackground(Background *bg, int LargeurFenetre, int HauteurFenetre, int Ecran) {
    bg->camera_pos_x.x = 0;
    bg->camera_pos_y.y = 0;
    bg->camera_pos_x.w = LargeurFenetre / Ecran;
    bg->camera_pos_y.h = HauteurFenetre / Ecran;
    bg->direction = 0;
}

void scrolling(Background *bg, int direction, int dx, int dy, int hauteurEcran) {
    // Si la direction est vers la droite (1)
    if (direction == 1) {
        bg->camera_pos_x.x += dx;
    }
    // Si la direction est vers la gauche (2)
    else if (direction == 2) {
        bg->camera_pos_x.x -= dx;
    }
    // Si la direction est vers le haut (3) et dépassement de la limite supérieure de l'écran
    else if (direction == 3 && bg->camera_pos_y.y > 0) {
        bg->camera_pos_y.y -= dy;
    }
    // Si la direction est vers le bas (4) et dépassement de la limite inférieure de l'écran
    else if (direction == 4 && bg->camera_pos_y.y < hauteurEcran) {
        bg->camera_pos_y.y += dy;
    }
}
