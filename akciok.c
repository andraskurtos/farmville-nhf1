#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "temp.h"
#include "debugmalloc.h"



// debughoz
/*void printfield(Field mezo, Plant* plants) {
        int i=0; while (plants[i].type != mezo.type) i++;
        printf("Tipusa: %s\nTexturaja: %s\nnovesi ideje: %d\nlocsolasi ideje: %d\n", plants[i].name, plants[i].texture, plants[i].growth, plants[i].water);
}*/



// jatek kezdese

// egy noveny adatainak megkeresese
Plant novenykeres(plantType type) {
    int i=0; while(novenyek[i].type != type) i++;
    return novenyek[i];
}


//noveny meglocsolasa
void locsol(int x, int y) {
    tabla[x][y].watertime = novenykeres(tabla[x][y].type).water; // visszaallitja a watertime-ot
}

//noveny ultetese
void ultet(int x, int y, plantType noveny) {
    tabla[x][y].type=noveny; //   novenytipus bemasolasa
    Plant adatok = novenykeres(noveny); //    adott noveny adatainak keresese
    tabla[x][y].growthtime = adatok.growth; //     alap novekedesi ido atirasa
    tabla[x][y].watertime = adatok.water; //       alap locsolasi ido atirasa
    tabla[x][y].status = planted; //      mas novenyeknel a status 'elultetett'/'elo' lesz (planted)

}

// ultetes felteteleinek vizsgalata es pontozas
void player_ultet(int x, int y, plantType noveny) {
            bool can_plant = (tabla[x][y].type == dirt) && (tabla[x][y].unlocked); // csak unlockolt foldre ultethetunk
            Plant adatok = novenykeres(noveny);
            if (points >= adatok.cost && can_plant) {
                ultet(x,y,noveny);
                points -= adatok.cost; // pont levonasa az ultetesert
                pointupd = true; // pontok ujrarajzolasa
            }
}
// noveny aratasa
void arat(int x, int y) {
    if(tabla[x][y].status == grown) { // ha megnott
        Plant adatok = novenykeres(tabla[x][y].type);
        ultet(x,y,dirt); // foldet rakunk a helyere
        points += adatok.yield; // megkapjuk a pontjutalmat
        pointupd = true;
    }
}

void vesz(int x, int y) { // mezo vasarlasa
    if (points>=fieldcost+2 && !tabla[x][y].unlocked) {
        points -= fieldcost; // az arat levonjuk a pontokbol.
        tabla[x][y].unlocked = true; // unlocked lesz az adott mezo
        fieldcost = (fieldcost*100*(100+(87-MERET*10))/10000); // a mezo ara ez alapjan scale-el
        pointupd = true;
    }
}


