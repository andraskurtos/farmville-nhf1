#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <SDL_ttf.h>
#include "debugmalloc.h"


// a növény állapotait tárolja (ültetve/megnott/fele)
typedef enum plantStatus {
        planted, grown, half
} plantStatus;




// növények típusai
typedef enum plantType {
        wheat, potato, carrot, beet, dirt
} plantType;

// struktúra egy növény adatainak tárolásához
typedef struct Plant {
        plantType type; // tipusa
        int growth; // növéshez szükséges idõ
        int water; // locsolás timer
        int yield; // "mennyit ad" az aratás
        int cost;
        char texture[60]; // textura fájlja
} Plant;

SDL_Renderer *renderer; // globalisan megadva hogy egyszerubben hasznalhassak a fuggvenyek


// egy adott mezot ír le a struktúra
typedef struct Field {
        plantType type; // beleültetett növény
        int growthtime; // hátralévõ növési idõ (folyamatosan frissül majd)
        int watertime; // locsolási idõ (ugyanúgy)
        plantStatus status; // állapota
        bool unlocked;

} Field;

// gombok tipusai
typedef enum buttonType {
    wheatbut, potatobut, carrotbut, beetbut, water, buy, nothing, save, load, num, newbutton
} buttonType;


// ezekkel a gombokkal választhatjuk majd az akciókat
typedef struct Button{
    buttonType type;
    char textura[40];
    int x;
    int y;
    int meret;
} Button;

// globalis valtozok
Field** tabla; // tabla
int points; // pontok szama
bool pointupd; // pont frissulese, ezzel iratjuk ki a pontokat
int fieldcost; // kovetkezo mezo ara
TTF_Font *font; // betutipus
int saveloc; // mentes / betoltes helye, uj jatek inditasakor pedig a tabla merete, a szamos gombbal valtoztathato
int MERET; // tabla merete
buttonType pressed; // éppen lenyomott gomb

// gombok adatai
static Button buttons[] = {
{wheatbut,"textures/wheat/button", 615,80,70},
{potatobut,"textures/potato/button", 690,80,70},
{carrotbut,"textures/carrot/button", 615,155,70},
{beetbut,"textures/beet/button",690,155,70},
{water,"textures/waterbutton",615,230,70},
{buy, "textures/buybutton",690,230,70},
{save,"textures/savebutton", 615, 305, 70},
{load, "textures/loadbutton", 690, 305, 70},
{num, "textures/but", 690, 380, 70},
{newbutton, "textures/newbutton", 615, 380, 70}};


// itt tárolódnak az adott növények adatai
static Plant novenyek[5] = {
    {wheat, 60, 30, 6, 2, "textures/wheat/"},
    {potato, 120, 40, 150, 50, "textures/potato/"} ,
    {carrot, 90, 10, 1000, 300, "textures/carrot/"},
    {beet,160,40,12000,5000,"textures/beet/"},
    {dirt, -1, -1, 0,-1, "textures/dirt.png"},
    };



// rajzol.c fuggvenyei
SDL_Texture* textura(plantType noveny,plantStatus status);
void mezorajzol(int x, int y);
void tablarajzol(void);
void vonalrajzol(int x, int y);
void buttondraw(Button but);
void drawallbuttons(void);
void textbox(char* str, int x, int y, TTF_Font* font);

// akciok.c fuggvenyei
Plant novenykeres(plantType type);
void locsol(int x, int y);
void ultet(int x, int y, plantType noveny);
void player_ultet(int x, int y, plantType noveny);
void vesz(int x, int y);
void arat(int x, int y);

//clickevent.c fuggvenyei
void hova(int x, int y);
void mezoclick(int x, int y);

//timemanagement.c fuggvenyei
void progress(void);

//save.c fuggvenyei
void init(void);
void freetabla(void);
void newgame(int size);
void saver(void);
void loader(void);

//pontok.c fuggvenyei
void writepoints(void);
void mezoar(void);



