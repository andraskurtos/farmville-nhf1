#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <SDL_ttf.h>
#include "temp.h"
#include "debugmalloc.h"



//      noveny texturajanak keresese
//      a növények adatai a globális "novenyek" nevû tömbben tárolódnak, innen kell kikeresnünk a textúrát
SDL_Texture* textura(plantType noveny, plantStatus status) {
    char texture[60];
    for (int i=0; ;++i) {
        if (novenyek[i].type == noveny) strcpy(&texture, &novenyek[i].texture); // megkeressük a novenyek-ben az elemet, aminek a tipusa egyezik a bekért tipussal, majd elkerjuk a texturajat
        if (novenyek[i].type==dirt) break;
    }
    if(noveny!=dirt) {
            switch(status) {
                case planted:
                    strcat(texture,"seed.png");
                    break;
                case half:
                    strcat(texture,"half.png");
                    break;
                case grown:
                    strcat(texture,"grown.png");
                    break;
            }
    }
    //printf("%s\t",texture);
    SDL_Texture* resource = IMG_LoadTexture(renderer, texture); // betöltjük a textúrát a rajzoláshoz

    if (resource == NULL) {
            printf("Textura beolvasasa sikertelen %d\n", noveny); // ha nem tudja betölteni hibaüzenet
    }

    return resource; // visszatérünk a textúrával
}


// egy mező kirajzolása
void mezorajzol(int x, int y) {
    SDL_Rect dest = {x*90+20,y*90+20,80,80}; // destination téglalap
    SDL_Texture* dirtT = IMG_LoadTexture(renderer,tabla[x][y].unlocked?"textures/dirt.png":"textures/dirt_locked.png");
    SDL_RenderCopy(renderer, dirtT, NULL, &dest); // kirajzolja alá a földet
    SDL_DestroyTexture(dirtT);
    if (tabla[x][y].type != dirt) {
            SDL_Texture* plant = textura(tabla[x][y].type,tabla[x][y].status);
            SDL_RenderCopy(renderer, plant, NULL, &dest); // kirajzolja a növényt
            SDL_DestroyTexture(plant); // töröljük a textúrákat, hogy ne foglalják a helyet

    }
    vonalrajzol(x,y);
}

void tablarajzol(void) { // végigloopol a táblán és kirajzolja azt
    for (int x=0;x<MERET;x++) {
        for (int y=0;y<MERET;y++) {
            mezorajzol(x, y);
        }
    }
}

void vonalrajzol(int x, int y) { // a mezok alatti vizallast mutato vonalat rajzolja
    int linelength;
    boxRGBA(renderer, x*90+20, y*90+102, x*90+100, y*90+105, 220, 220, 220, 255); // a szurke hatter a vonalon
    if (tabla[x][y].type == dirt | tabla[x][y].status == grown) linelength = 0;
    else {

        linelength = 8000/((novenykeres(tabla[x][y].type).water*100)/tabla[x][y].watertime); // kek vonal hossza a vizallas alapjan
        //printf("%d\t", linelength);
        boxRGBA(renderer, x*90+20, y*90+102, x*90+20+linelength, y*90+105, 0, 100, 255, 255); //kek vonal rajzolasa
    }
}

//  kirajzol egy gombot
void buttondraw(Button but) {
    SDL_Rect dest = {but.x,but.y,but.meret,but.meret};
    char resource[60];
    if(but.type == num) sprintf(resource, "textures/numbers/%d", saveloc);
    else strcpy(resource, but.textura);
    if(but.type == pressed) strcat(resource,"_down");
    strcat(resource,".png");
    SDL_Texture* texture = IMG_LoadTexture(renderer,resource);
    if (texture == NULL) printf("textura betoltese nem sikerult\n");
    else {
            SDL_RenderCopy(renderer,texture,NULL,&dest);
            SDL_DestroyTexture(texture);
    }
}

void drawallbuttons(void) { // osszes gombot kirajzolja
    for (int i=0;i<10;i++) {
        buttondraw(buttons[i]);
    }
}

// kiir egy szoveget
void textbox(char* str, int x, int y, TTF_Font* font) {
    SDL_Color col = {40,115,31}; // szin beallitasa
    SDL_Surface *text;
    SDL_Texture *textT;
    text = TTF_RenderUTF8_Blended(font, str, col);
    textT = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect dest = {x,y,text->w,text->h};
    SDL_RenderCopy(renderer, textT, NULL, &dest);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(textT);

}


