#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "temp.h"
#include <SDL_ttf.h>
#include "debugmalloc.h"

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

int iter =0;
Uint32 updatetime(Uint32 ms, void *param) {

            if (pointupd) {

                boxRGBA(renderer, 574, 0, 800, 600, 220, 220, 220, 255);
                textbox("FARMVILLE", 615, 15, font);
                writepoints();
                mezoar();
                pointupd = false;
            }


            tablarajzol();
            drawallbuttons();

            SDL_RenderPresent(renderer);
    iter++;
    if(iter ==10) {iter =0;progress();/*points++;pointupd = true;*/}
    return ms;   /* ujabb varakozas */
}






int main(int argc, char *argv[]) {
    /* ablak letrehozasa */
    SDL_Window *window;

    sdl_init("farmville", 800, 600, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 74, 94, 69, 255);
    SDL_RenderClear(renderer);
    TTF_Init(); // betutipus betoltese
    font = TTF_OpenFont("custom.ttf", 26);
    if (!font) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }

    //alapbeallitasok
    points = 0;
    pressed = nothing;
    bool click = false;
    int cursorx = 0;
    int cursory = 0;
    pointupd = true;
    fieldcost = 16;
    saveloc = 1;

    SDL_RenderPresent(renderer);



    SDL_TimerID idoupdate = SDL_AddTimer(100, updatetime, NULL);

    /* varunk a kilepesre */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch(ev.type) {
            case SDL_MOUSEBUTTONDOWN:
                    if (ev.button.button==SDL_BUTTON_LEFT) {

                        cursorx=ev.button.x;
                        cursory=ev.button.y;
                        if (cursorx != 0 && cursory != 0) click = true;

                        hova(cursorx, cursory);
                    }
         }

    }

    /* ablak bezarasa */
    TTF_CloseFont(font);
    SDL_Quit();
    freetabla();

    debugmalloc_dump();
    debugmalloc_log_file("debuglog.txt");

    return 0;
}
