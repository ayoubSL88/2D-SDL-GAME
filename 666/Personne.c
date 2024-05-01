#include "Personne.h"
#include <stdio.h>
#include <stdlib.h>

#define GRAVITY 0.5

void initPerso(Personne *p)
{
    int i, j;
    char nom_image[30];
    p->acceleration = 0;
    p->direction = 0;
    p->nbr_frame = 0;
    p->up = 0;
    p->ground = 200;
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
    if (p->direction == 0)
    {
        if (p->position.x < 960)
            p->position.x = p->position.x + p->dx;
    }
    else if (p->direction == 1)
    {
        if (p->position.x > 100)
            p->position.x = p->position.x - p->dx;
    }

    if (p->up)
    {
        p->position.y += p->vitesse_saut * dt;
        p->vitesse_saut += GRAVITY * dt;

        if (p->position.y >= p->ground)
        {
            p->position.y = p->ground;
            p->vitesse_saut = 0;
            p->up = 0;
        }
    }
}

void saut(Personne *p)
{
    if (p->position.y == p->ground)
    {
        p->vitesse_saut = -10;
        p->up = 1;
    }
}

