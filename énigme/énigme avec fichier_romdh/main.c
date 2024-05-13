#include "enigme.h"
#include "input.h" 


void main()
{
    

	Input I;
    enigme f;
    bool running=true;
	SDL_Event event;
    
	SDL_Surface *screen, *bg ,*tr,*hero,*choix; 
    SDL_Rect bgpos;
	
      init_input(&I);
    
	      SDL_Init(SDL_INIT_VIDEO );
    screen = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Lunatics", NULL); 
    
	bg=IMG_Load("Assets/graphic/stages/backgtest.jpg");
	bgpos.x=0;
	bgpos.y=0;

	 tr=IMG_Load("Assets/graphic/trea.jpeg");
	SDL_Rect trpos;
	trpos.x=600;
	trpos.y=500;

	 SDL_Rect heropos;
    heropos.x = 20;
    heropos.y = 480;
    heropos.w=200;
    heropos.h=200;

hero = IMG_Load("Assets/graphic/hero/hero_test.png");
SDL_Rect poschoix;
poschoix.x=600;
poschoix.y=400;
choix= IMG_Load("Assets/graphic/EEE.png");


Init_enigme(&f); 
SDL_EnableKeyRepeat(200,0);
while(running)
{

while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
        SDL_Quit();
			running=false;
		break; 
        case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_RIGHT:
				heropos.x+=10;
                 break;
				 case SDLK_LEFT:
				heropos.x-=10;
                 break;
				 case SDLK_e:
				 I.e=1;
				 break;
				 
			}  
		break;

        case SDL_KEYUP:
			switch (event.key.keysym.sym) 
			{
			/*case SDLK_e:
			I.e=0;

			break;*/
			

			}
		break;
	    }
    } 


SDL_BlitSurface(bg,NULL,screen,&bgpos); 
SDL_BlitSurface(tr,NULL,screen,&trpos);
SDL_BlitSurface(hero,NULL,screen,&heropos);
if(heropos.x-trpos.x>-200&&heropos.x-trpos.x<=200) 
{
SDL_BlitSurface(choix,NULL,screen,&poschoix);

}
if(heropos.x-trpos.x>-200&&heropos.x-trpos.x<=200&&I.e==1)
{

	afficherEnigme(&f); 
}
else
{
	I.e=0;
}
SDL_Flip(screen);
SDL_Delay(16); 
} 
}
