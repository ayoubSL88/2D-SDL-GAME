#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

#define MINIMAP_WIDTH 500
#define MINIMAP_HEIGHT 30
void initmap( minimap * m)
{
	m->img_map=IMG_Load("minimap.png");
	m->img_joueur=IMG_Load("mini_joueur.png"); 

	m->pos_map.x=0;
	m->pos_map.y=0;
}


SDL_Rect MAJMinimap (SDL_Rect Posjoueur,int redemensionement,SDL_Rect camera, int minimapWidth, int minimapHeight)
{
	SDL_Rect pos_joueur;
    pos_joueur.x = ((camera.x + Posjoueur.x) * redemensionement) / 100;
    pos_joueur.y = ((camera.y + Posjoueur.y) * redemensionement) / 100;
    
    if (pos_joueur.x < 0)
     
   pos_joueur.x = 0;
    else if (pos_joueur.x > minimapWidth - Posjoueur.w)
        pos_joueur.x = minimapWidth - Posjoueur.w;

    if (pos_joueur.y < 0)
        pos_joueur.y = 0;
    else if (pos_joueur.y > minimapHeight - Posjoueur.h)
        pos_joueur.y = minimapHeight - Posjoueur.h;

    return pos_joueur;
}
	



void afficherminimap(minimap m, SDL_Surface *screen, SDL_Rect playerPosition)
{
	SDL_BlitSurface(m.img_map,NULL,screen,&m.pos_map);
        
        SDL_Rect relativePlayerPosition;
        relativePlayerPosition.x = (playerPosition.x - m.pos_map.x) * (m.pos_map.w / MINIMAP_WIDTH);
        relativePlayerPosition.y = (playerPosition.y - m.pos_map.y) * (m.pos_map.h / MINIMAP_HEIGHT);
        m.pos_joueur.x = playerPosition.x;  
        m.pos_joueur.y = playerPosition.y;

   
    if (m.pos_joueur.x < m.pos_map.x)
        m.pos_joueur.x = m.pos_map.x;
    else if (m.pos_joueur.x > m.pos_map.x + m.pos_map.w - m.img_joueur->w)
        m.pos_joueur.x = m.pos_map.x + m.pos_map.w - m.img_joueur->w;

    if (m.pos_joueur.y < m.pos_map.y)
        m.pos_joueur.y = m.pos_map.y;
    else if (m.pos_joueur.y > m.pos_map.y + m.pos_map.h - m.img_joueur->h)
        m.pos_joueur.y = m.pos_map.y + m.pos_map.h - m.img_joueur->h;

	SDL_BlitSurface(m.img_joueur,NULL,screen,&m.pos_joueur);
}


void affichertemp (Uint32 *temps,SDL_Surface *screen,TTF_Font *police)
{

	SDL_Surface *chrono = NULL;
	SDL_Rect positionChrono;
	SDL_Color couleur = {255,255,255};

	int min=0,sec=0;
	char texteChrono [40] = "";

	positionChrono.x = 840;
	positionChrono.y = 10;

	(*temps)=SDL_GetTicks();
	(*temps)/=1000;
	min=((*temps)/60);
	sec=(*temps) - (60*min);

	sprintf(texteChrono,"%02d:%02d",min,sec);

	SDL_FreeSurface(chrono);
	chrono = TTF_RenderText_Solid(police,texteChrono,couleur);
	SDL_BlitSurface(chrono,NULL,screen,&positionChrono);
	
}


SDL_Color GetPixel(SDL_Surface *mask,int x,int y)
{
	SDL_Color color;
	Uint32 col=0;

	char * pPosition=(char*)mask->pixels;

	pPosition+=(mask->pitch *y);
	pPosition+=(mask->format->BytesPerPixel *x);
	memcpy(&col,pPosition,mask->format->BytesPerPixel);

	
	SDL_GetRGB(col,mask->format,&color.r,&color.g,&color.b);
	return(color);
}


int collisionPP_droite( SDL_Rect posjoueur, SDL_Surface *mask,SDL_Rect camera)
{
	int collision=0;
	int i;

	SDL_Color couleur_obstacle={0,0,0},test;
	

	int pos[3][2];
	pos[0][0]=100+camera.x+posjoueur.x+posjoueur.w;
	pos[0][1]=120+posjoueur.y;
	pos[1][0]=100+camera.x+posjoueur.x+posjoueur.w;
	pos[1][1]=120+posjoueur.y+posjoueur.h/2;
	pos[2][0]=100+camera.x+posjoueur.x+posjoueur.w;
	pos[2][1]=120+posjoueur.y+posjoueur.h;
	for(i=0;i<2 && collision==0;i++)
	{
		test=GetPixel(mask,pos[i][0],pos[i][1]);
		if ((test.r==couleur_obstacle.r)&&(test.g==couleur_obstacle.g)&&(test.b==couleur_obstacle.b))
			collision=1;
			
	}
	return collision;
}


int collisionPP_gauche( SDL_Rect posjoueur, SDL_Surface *mask,SDL_Rect camera)
{
	int collision=0;
	int i;

	SDL_Color couleur_obstacle={0,0,0},test;
	

	int pos[3][2];
	pos[0][0]=100+camera.x+posjoueur.x;
	pos[0][1]=120+posjoueur.y;
	pos[1][0]=100+camera.x+posjoueur.x;
	pos[1][1]=120+posjoueur.y+posjoueur.h/2;
	pos[2][0]=100+camera.x+posjoueur.x;
	pos[2][1]=120+posjoueur.y+posjoueur.h;

	for(i=0;i<2 && collision==0;i++)
	{
		test=GetPixel(mask,pos[i][0],pos[i][1]);
		if ((test.r==couleur_obstacle.r)&&(test.g==couleur_obstacle.g)&&(test.b==couleur_obstacle.b))
			collision=1;
			

	}
	return collision;
}




int collisionPP_up( SDL_Rect posjoueur, SDL_Surface *mask,SDL_Rect camera)
{
	int collision=0;
	int i;

	SDL_Color couleur_obstacle={0,0,0},test;

	int posX,posY;
	posX=100+camera.x+ posjoueur.x+ posjoueur.w/2;
	posY=120+posjoueur.y;

	test=GetPixel(mask,posX,posY);
	if ((test.r==couleur_obstacle.r)&&(test.g==couleur_obstacle.g)&&(test.b==couleur_obstacle.b))
		collision=1;

	return collision;
}


int collisionPP_down( SDL_Rect posjoueur, SDL_Surface *mask,SDL_Rect camera)
{
	int collision=0;
	int i;
	SDL_Color couleur_obstacle={0,0,0},test;
	
	int posX,posY;
	posX=100+camera.x+ posjoueur.x+ posjoueur.w/2;
	posY=120+posjoueur.y+ posjoueur.h;

	test=GetPixel(mask,posX,posY);
	if ((test.r==couleur_obstacle.r)&&(test.g==couleur_obstacle.g)&&(test.b==couleur_obstacle.b))
		collision=1;

	return collision;
}

