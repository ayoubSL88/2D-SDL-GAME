#ifndef ENTITY_H
#define ENTITY_H

#include <SDL/SDL.h>

#define LARGEUR_SPRITE 32
#define HAUTEUR_SPRITE 32
#define VITESSE_ANIMATION 100 // Vitesse de l'animation en millisecondes

typedef struct {
    SDL_Surface* spriteSheet;
    SDL_Rect posSprite;
    int direction;
    int numFrames; // Nombre total de frames dans le sprite sheet
    int currentFrame; // Frame actuelle
    Uint32 lastFrameTime; // Temps écoulé depuis la dernière frame
} Entity;

void initializeEntity(Entity *entity, const char* spriteSheetFile, int numFrames);
void animateEntity(Entity *entity);
void blitEntity(Entity *entity, SDL_Surface *screen);

#endif

