#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "temp.h"
#include "debugmalloc.h"


void writepoints(void) { // pontok kiirasa
    char str1[] = "$";
    int len = (points != 0)?(strlen(str1) + floor(log10(points))+1):2; // szam karakterszamanak kiszamolasa
    //printf("%d", len);
    char* str2 = (char*) malloc((len+1)*sizeof(char)); // foglalas a kiirando stringnek
    sprintf(str2,"%d",points);
    strcat(str2,str1);
    textbox(str2, 615, 40, font); // string kiirasa
    free(str2); // felszabaditas
}

void mezoar(void) {
    int len =  floor(log10(fieldcost))+6;
    char* str1 = (char*) malloc((len+1)*sizeof(char)); // foglalas
    sprintf(str1,"%d(+2)$",fieldcost);
    textbox(str1,640,500,font); // kiiras
    free(str1); // felszabaditas
}
