#include <stdlib.h>
#include <stdio.h>
#include "temp.h"
#include "debugmalloc.h"


// ido leptetese
void progress(void) {
        for (int x=0;x<MERET;x++) {
            for (int y=0;y<MERET;y++) {

                if (tabla[x][y].growthtime>0) tabla[x][y].growthtime--;// hatralevo novesi idok csokkentese
                if (tabla[x][y].watertime>0) tabla[x][y].watertime--; // locsolasi idok csokkentese
                if (tabla[x][y].growthtime<novenykeres(tabla[x][y].type).growth/2 && tabla[x][y].status != half) tabla[x][y].status = half; // felig megnott allapot beallitasa
                if (tabla[x][y].growthtime==0 && tabla[x][y].status!=grown) {
                        tabla[x][y].status = grown; //  noveny megnovesztese
                        tabla[x][y].watertime = -1;
                }
                if (tabla[x][y].watertime ==0) {
                        if (points == 0) {points += 2; pointupd=true;}
                        ultet(x,y,dirt);} // noveny kiszaradasa


            }
        }
}


