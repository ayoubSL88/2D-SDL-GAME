#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "enemy.h"
#include "Personne.h"

Enemy InitEnemy(Enemy Ennemie, int x, int y)
{
    Ennemie.image[0] = IMG_Load("rpg1.png");
    Ennemie.image[1] = IMG_Load("rpg2.png");
    Ennemie.image[2] = IMG_Load("rpg3.png");

    Ennemie.image2[0] = IMG_Load("rpd1.png");
    Ennemie.image2[1] = IMG_Load("rpd2.png");
    Ennemie.image2[2] = IMG_Load("rpd3.png");
    Ennemie.imageActuel = Ennemie.image[0];
    Ennemie.position.x = x;
    Ennemie.position.y = y;
    Ennemie.positionO = Ennemie.position;
    Ennemie.frame = 0;
    Ennemie.direction = 0;
    return Ennemie;
}

void AfficherEnemy(Enemy Ennemie, SDL_Surface *screen)
{
    SDL_BlitSurface(Ennemie.imageActuel, NULL, screen, &Ennemie.position);
}

Enemy AnimateEnemy(Enemy Ennemie, int stat)
{
    if (Ennemie.frame == 2)
    {
        Ennemie.frame = 0;
    }
    else
        Ennemie.frame++;
    if (Ennemie.direction == 1)
        Ennemie.imageActuel = Ennemie.image[Ennemie.frame];
    else if (Ennemie.direction == 0)
        Ennemie.imageActuel = Ennemie.image2[Ennemie.frame];
    if (stat == 1)
        Ennemie.imageActuel = Ennemie.Hit;
    return Ennemie;
}

Enemy MoveEnemy(Enemy Ennemie, SDL_Rect personnage, int *stat, int mouvement)
{
    int distance;

    if (Ennemie.position.x >= personnage.x)
        distance = Ennemie.position.x - personnage.x;
    else
        distance = personnage.x - Ennemie.position.x;
    if (distance < 50)
        *stat = 1;
    else
        *stat = 0;
    if (distance < 80)
    {
        if (Ennemie.position.x >= personnage.x)
            Ennemie.direction = 0;
        else
            Ennemie.direction = 1;
    }
    else
    {
        if (Ennemie.positionO.x + 80 <= Ennemie.position.x)
            Ennemie.direction = 0;

        if (Ennemie.positionO.x - 80 >= Ennemie.position.x)

            Ennemie.direction = 1;
    }

    if (Ennemie.direction == 1)
    {
        Ennemie.position.x += 4;
    }
    if (Ennemie.direction == 0)
    {
        Ennemie.position.x -= 4;
    }

    if (mouvement == 1)
    {
        Ennemie.position.x -= 5;
        Ennemie.positionO.x -= 5;
    }
    if (mouvement == 2)
    {

        Ennemie.position.x += 5;
        Ennemie.positionO.x += 5;
    }
    if ((mouvement == 3) && (personnage.y > 50))
    {
    }
    return Ennemie;
}

Bonus initBonus(Bonus bonus, int x, int y)
{
    bonus.image = IMG_Load("coin.png");
    if (!bonus.image)
    {
        printf("Failed to load coin image: %s\n", IMG_GetError());
        bonus.collected = 1; // Set collected to 1 if failed to load image
        return bonus;
    }
    bonus.position.x = x;
    bonus.position.y = y;
    bonus.collected = 0; // Set collected to 0 as default
    return bonus;
}

void AfficherBonus(Bonus bonus, SDL_Surface *screen)
{
    SDL_BlitSurface(bonus.image, NULL, screen, &bonus.position);
}

int collisionBonus(Personne *p, Bonus *bonus)
{
    if ((p->position.x + p->position.w >= bonus->position.x) &&
        (p->position.x <= bonus->position.x + bonus->position.w) &&
        (p->position.y + p->position.h >= bonus->position.y) &&
        (p->position.y <= bonus->position.y + bonus->position.h))
    {
        return 1; // Collision detected
    }
    return 0; // No collision
}

void collecterBonus(Personne *p, Bonus *bonus)
{
    bonus->collected = 1; // Set collected to 1
}

