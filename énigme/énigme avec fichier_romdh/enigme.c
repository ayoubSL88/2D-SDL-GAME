#include "enigme.h"
#include "input.h" 


int Init_enigme(enigme *g ) 
{ char quest1[100],choix1[100],choix2[100],win[100],lose[100],rep1[3],line[300];
int i,j;
    FILE *fichier = NULL;
    fichier= fopen("text.txt","r");
   i=genererEnigme();
    if(fichier!=NULL)

    {
      
      for(j=0;j<i+1;j++)
      {
         fgets(line,300,fichier) ;
      }
     
char * token = strtok(line, " "); 
 
   
    
    strcpy(choix1,token);
    token = strtok(NULL, " "); 

    strcpy(choix2,token);
    token = strtok(NULL, " ");

    strcpy(rep1,token);
    token = strtok(NULL, " ");
 
    strcpy(quest1,token);
     token = strtok(NULL, " ");

    strcpy(win,token);
    token = strtok(NULL, " ");
 
    strcpy(lose,token);
      
    }


g->pos.x=450;
g->pos.y=200;
g->reponse= IMG_Load(choix1);
g->reponse1= IMG_Load(choix2); 
g->enigme= IMG_Load(quest1);

g->reponse_pos.x = 0;
g->reponse_pos.y = 0;


g->t=IMG_Load(win);
g->h = IMG_Load(lose);
strcpy(g->rep,rep1);

  
}


void afficherEnigme(enigme *e)
{ 

    SDL_Surface * screen;
    screen = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Lunatics", NULL); 

   
    bool running=true;
	int i;
	int yesIndex = 0, noIndex = 0;
     Input I;
     I.Return=0;
    
  

   
	SDL_Event event;

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
				case SDLK_KP1:
                if (strcmp(e->rep,"1")==0)
                {
                    SDL_BlitSurface(e->t, NULL, screen, &e->reponse_pos);
                    SDL_Flip(screen);
                    SDL_Delay(16);
                }
                else
                {
                   SDL_BlitSurface(e->h, NULL, screen, &e->reponse_pos);
                   SDL_Flip(screen);
                   SDL_Delay(16); 
                  
                }
               
                
                break;

            case SDLK_KP2:
            if (strcmp(e->rep,"2")==0)
                {
                    SDL_BlitSurface(e->t, NULL, screen, &e->reponse_pos);
                    SDL_Flip(screen);
                    SDL_Delay(16);
                }
                else
                {
                   SDL_BlitSurface(e->h, NULL, screen, &e->reponse_pos);
                   SDL_Flip(screen);
                   SDL_Delay(16);  
                }
               
                break;
			}  
		break;

        case SDL_KEYUP:
			switch (event.key.keysym.sym) 
			{	
				
			}
		break;
	    }
    }


    if(I.Return != 1)
      {
     SDL_BlitSurface(e->enigme,NULL,screen,&e->pos);
     SDL_BlitSurface(e->reponse,NULL,screen,&e->reponse_pos);  
     SDL_BlitSurface(e->reponse1,NULL,screen,&e->reponse_pos);
    
      }
SDL_Flip(screen);
SDL_Delay(16); 
} 

}


int genererEnigme()
{
int i ;
srand(time(NULL));
i=(rand()%2);
 return i ;
}


