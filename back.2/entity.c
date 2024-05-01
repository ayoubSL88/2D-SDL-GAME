#include "entity.h"
#include <SDL/SDL_image.h>

void initializeEntity(Entity *entity, const char* spriteSheetFile, int numFrames) {
    entity->spriteSheet = IMG_Load(spriteSheetFile);
    if (!entity->spriteSheet) {
        printf("Erreur lors du chargement du sprite sheet : %s\n", IMG_GetError());
        return;
    }
    entity->posSprite.x = 0;
    entity->posSprite.y = 0;
    entity->posSprite.w = LARGEUR_SPRITE;
    entity->posSprite.h = HAUTEUR_SPRITE;
    entity->direction = 0;
    entity->numFrames = numFrames;
    entity->currentFrame = 0;
    entity->lastFrameTime = SDL_GetTicks(); // Initialisation du temps de la dernière frame
}

void animateEntity(Entity *entity) {
    Uint32 now = SDL_GetTicks();
    if (now - entity->lastFrameTime > VITESSE_ANIMATION) {
        entity->lastFrameTime = now;
        entity->currentFrame++;
        if (entity->currentFrame >= entity->numFrames) {
            entity->currentFrame = 0; // Revenir à la première frame
        }
        entity->posSprite.x = entity->currentFrame * LARGEUR_SPRITE; // Calcul de la position de la frame dans le sprite sheet
    }
}

void blitEntity(Entity *entity, SDL_Surface *screen) {
    SDL_BlitSurface(entity->spriteSheet, &entity->posSprite, screen, NULL);
}

