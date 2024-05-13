#ifndef FONCTIONS_H_
#define FONCTIONS_H_
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>
#define LARGEUR_ECRAN 700
#define HAUTEUR_ECRAN 700
#define LARGEUR_IMAGE_BACKGROUND 3192
#define LARGEUR_JOUEUR 50
#define HAUTEUR_JOUEUR 50
#define VITESSE_JOUEUR_X 13
#define VITESSE_JOUEUR_Y 13
#define VITESSE_DEFILEMENT_X 5
#define VITESSE_DEFILEMENT_Y 5
#define VITESSE_SAUT 200
#define GRAVITE 10
#define ZOOM_FACTOR 2
 SDL_Surface *screen;




typedef struct {
	int x,y;
	int h,w;
	int indicebtn;
}bouton;
typedef struct {
    int x, y, w, h;
} Camera;

typedef struct {
    int x, y;
    SDL_Surface *sprite;
} Joueur;

typedef struct {
    SDL_Rect posBack1;
    SDL_Rect posBack2;
    SDL_Rect posEcran;
    int scrollX1;
    int scrollX2;
    SDL_Surface *image;
} Background;

typedef enum {
    Waiting,
    Following,
    Attacking
} EnemyState;

typedef struct {
    EnemyState state;
} Enemy;
void displayHighScores();
void loadtext1(char text[] , char cheminfont[], int taille , int indcouleur, int x , int y , SDL_Surface *ecran);
int lire_scores_et_trouver_max(const char *fichier_scores, const char *fichier_rank1);
char *lire_ligne(const char *nom_fichier);
char *lireMeilleurScore();
void afficherMeilleurScore(SDL_Surface *ecran);
void afficherBackground(Background *background, int joueur);
void animerBack(int *frame);
void afficherScore(int score, SDL_Surface *backgroundSurface);
void afficherJoueur(Joueur *joueur);
void loadSunImages();
void initialiserBackground(Background *background, char *imagePath);
SDL_Surface *loadImage(char *filename);
void initialiserJoueur(Joueur *joueur, char *spritePath, int posX, int posY);
void initCamera(Camera *camera);
void saveScore(int score);
int readLastScore();
void initCamera(Camera *camera);
void displayHighScores();
int compareInts(const void *a, const void *b);
void dimenstionsBTN(SDL_Rect *btn1,SDL_Rect *btn2,SDL_Rect* btn3,SDL_Rect* btn4,SDL_Surface *btnclick0);
void loadbtns(SDL_Surface **play1, SDL_Surface **play2 ,SDL_Surface **rank1, SDL_Surface **rank2 , SDL_Surface **op1, SDL_Surface **op2, SDL_Surface **exit1, SDL_Surface **exit2);
bool sourisSurbtn(SDL_Rect btn, SDL_Event event);
void changetexture(SDL_Rect btn1, SDL_Rect btn2, SDL_Rect btn3, SDL_Rect btn4, SDL_Event event, 
SDL_Surface * play1,
SDL_Surface * play2,
SDL_Surface * rank1,
SDL_Surface * rank2,
SDL_Surface * op1,
SDL_Surface * op2,
SDL_Surface * exit1,
SDL_Surface * exit2,
 SDL_Surface *ecran); 

void loadlevel1(SDL_Surface *lvlback , SDL_Surface *ecran , SDL_Rect posback, Mix_Music *sonbref ) ;
void loadtext (char text[] , char cheminfont[], int taille , int indcouleur, int x , int y , SDL_Surface *ecran); // 1 red , 2 green , 3 blue , 0 white , -1 black 
 
#endif
