#include <stdio.h>
#include <stdlib.h>
#include "temp.h"
#include "debugmalloc.h"

//>(o)
//   (_)<
//Lorrinc <3
//Kati was here :)

 // melyik gomb van eppen lenyomva

// kattintas helyenek vizsgalata
void hova(int x, int y) {
    for (int i=0;i<10;i++) // gombok megnezese
        if (x>buttons[i].x && y>buttons[i].y && x<buttons[i].x+buttons[i].meret && y<buttons[i].y+buttons[i].meret ){ // ha a gombon belul kattintunk
            //printf("KLIKK %s \n", buttons[i].textura);
           if(buttons[i].type == save && MERET != 0) saver(); // mentes
           else if (buttons[i].type == load) loader(); // betoltes
           else if (buttons[i].type == newbutton) newgame(saveloc); // uj jatek
           else if (buttons[i].type== num) saveloc = (saveloc==6)?1:(saveloc+1); // szamvalasztas
           else {
                if (pressed != buttons[i].type) pressed = buttons[i].type; // a tobbi gombnal lenyomodik a gomb
                    else pressed = nothing;
           }



        }
    // mezok megnezese
    for (int tx=0;tx<MERET;tx++) {
        for (int ty=0;ty<MERET;ty++) {
                int xkezd = tx*90+20;
                int ykezd = ty*90+20;
            if (x>xkezd && y>ykezd && x<xkezd+80 && y<ykezd+80) {
                //printf("KLIKK %d. sor %d. mezo! \n", ty+1, tx+1);
                mezoclick(tx,ty);
            }
        }
    }

}


// mezobe klikkeles vizsgalatas
void mezoclick(int x, int y /*a tablan belul ertendok sor es oszlopkent, nem xy koordinata*/) {
        switch (pressed) {
        case water: locsol(x,y); break; // mezo meglocsolasa
        case nothing: arat(x,y); break; // mezo aratasa
        case buy: vesz(x,y); break; // mezo vasasrlasa
        case wheatbut: player_ultet(x,y,wheat); break; // buza ultetes
        case potatobut: player_ultet(x,y,potato); break; // krumpli ultetes
        case carrotbut: player_ultet(x,y,carrot); break; // repa ultetes
        case beetbut:   player_ultet(x,y,beet); break; // cekla ultetes

        }
}


