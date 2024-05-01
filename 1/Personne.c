#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "Personne.h"

#define GRAVITY 0.5

void initPerso(Personne *p)
{
    int i, j;
    char nom_image[30];
    p->acceleration = 0;
    p->direction = 0;
    p->nbr_frame = 0;
    p->up = 0;
    p->ground = 200; // Set the ground level
    p->position.x = 400;
    p->position.y = p->ground;
    p->position.w = 115;
    p->position.h = 140;
    p->vitesse = 0;
    p->vitesse_saut = 0;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 4; j++)
        {
            sprintf(nom_image, "%d%d.png", i, j);
            p->images[i][j] = IMG_Load(nom_image);
            if (!p->images[i][j])
            {
                printf("Failed to load images %d,%d: %s\n", i, j, IMG_GetError());
            }
        }
    }
}

void afficherPerso(Personne p, SDL_Surface *screen)
{
    SDL_BlitSurface(p.images[p.direction][p.nbr_frame], NULL, screen, &p.position);
}

void animerPerso(Personne *p)
{
    p->nbr_frame++;
    if (p->nbr_frame >= 4)
        p->nbr_frame = 0;
    if ((p->vitesse == 0) && ((p->direction == 0) || (p->direction == 1)))
    {
        p->nbr_frame = 0;
    }
}

void deplacerPerso(Personne *p, int dt)
{
    p->dx = 2 * p->acceleration * dt * dt + p->vitesse * dt;
    if (p->direction == 0) //mvt droite
    {
        if (p->position.x < 960)
            p->position.x = p->position.x + p->dx;
    }
    else if (p->direction == 1)
    {
        if (p->position.x > 100)
            p->position.x = p->position.x - p->dx;
    }

    // Jump handling
    if (p->up)
    {
        p->position.y += p->vitesse_saut * dt; // Apply upward velocity
        p->vitesse_saut += GRAVITY * dt;       // Apply gravity to simulate jump arc

        // Check if the player has reached the ground level
        if (p->position.y >= p->ground)
        {
            p->position.y = p->ground; // Ensure the player is exactly at the ground level
            p->vitesse_saut = 0;       // Reset jump velocity
            p->up = 0;                 // End the jump
        }
    }
}

void saut(Personne *p)
{
    if (p->position.y == p->ground)
    {
        p->vitesse_saut = -10; // Set initial jump velocity
        p->up = 1;             // Set the flag to indicate jumping
    }
}

void initialiser_score(vie *v)
{
    v->vie = IMG_Load("health.png");
    if (!v->vie)
    {
        fprintf(stderr, "Failed to load health image: %s\n", IMG_GetError());
        return;
    }
    v->valeur_vie = 100;
    v->pos.x = 0;
    v->pos.y = 150;
    v->pos_spr.x = 0;
    v->pos_spr.y = 0;
    v->pos_spr.h = 50;
    v->pos_spr.w = 200;
}

