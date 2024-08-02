#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "temp.h"
#include "debugmalloc.h"

// tabla felszabaditasa
void freetabla(void) {
    for (int y=0;y<MERET;y++) free(tabla[y]); // sorok felszabaditasa
    free(tabla); // tabla felszabaditasa
}

// inicializalas
void init(void) {
    //tabla 2ds tombben tarolva
    boxRGBA(renderer, 0, 0, 800, 800, 74, 94, 69, 255);
    tabla = (Field**) malloc(MERET*sizeof(Field*)); // sorok lefoglalása
    if (tabla==NULL) {printf("Nem sikerult a memoriafoglalas"); exit(1);}
    for (int y=0;y<MERET;y++) {
            tabla[y] = (Field*) malloc(MERET*sizeof(Field)); // sorok elemeinek lefoglalása
            if (tabla[y]==NULL) {printf("Nem sikerult a memoriafoglalas"); exit(1);}
    }
    //tábla megtöltése az alapertelmezett elemekkel (föld)
    for(int x=0;x<MERET;x++) {
        for (int y=0;y<MERET;y++) {
            ultet(x,y,dirt);
            if(x>0 | y>1) tabla[x][y].unlocked = false;
            else tabla[x][y].unlocked = true;
        }
    }
}

// uj jatek
void newgame(int size) {
    freetabla(); // tabla felszabaditasa
    // meret atallitasa
    MERET = size; //printf("%d\n", MERET);

    init(); // inicializalas
    // alapertelmezett ertekek megadasa
    points = 22;
    fieldcost = 16;
    pointupd= true;
}

// mentes
void saver(void) {
    char filename[40];
    sprintf(filename, "saves/save%d.txt", saveloc); // mentes fajljananak kivalasztasa
    FILE *fp;
    fp = fopen(filename, "w"); // fajl megnyitasa
    if (fp==NULL) printf("fajl megnyitasa sikertelen");
        fprintf(fp, "%d\t%d\t%d\n", MERET, points, fieldcost); // elso sorba irodik a meret, a pontok es a kovetkezo mezo ara
        for (int x=0; x<MERET; x++) {
            for (int y=0; y<MERET; y++) {
                fprintf(fp, "%d\t%d\t%d\t%d\t%d\n", tabla[x][y].type, tabla[x][y].growthtime, tabla[x][y].watertime, tabla[x][y].status, tabla[x][y].unlocked); // kovetkezo sorokba az egyes mezok adatai irodnak
            }
        }

    fclose(fp);
}

// betoltes
void loader(void) {
    char filename[40];
    sprintf(filename, "saves/save%d.txt", saveloc); // fajlnev kivalasztasa
    FILE *fp;
    fp = fopen(filename, "r"); // megnyitas
    int size;
    fscanf(fp, "%d\t%d\t%d", &size, &points, &fieldcost); // elso sor beolvasasa, meret, pontok, mezoar
    pointupd = true;
    newgame(size);
    for (int x=0;x<MERET; x++) { // loop a sorokon, beirjuk az adatokat a tablaba
            // mivel a meret mar megvaltozott, a loopok egyutt pontosan a sorok szamaszor fognak lefutni
        for (int y=0; y<MERET;y++) {
            Field temp;
            fscanf(fp, "%d\t%d\t%d\t%d\t%d\n", &temp.type, &temp.growthtime, &temp.watertime,&temp.status, &temp.unlocked); // sorokbol beolvasasa a tabla adatainak
            tabla[x][y] = temp;
        }
    }
    fclose(fp);
}



