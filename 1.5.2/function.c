#include <SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, int* ms){
    Uint32 antes = SDL_GetTicks();
    int isevt = SDL_WaitEventTimeout(evt, *ms);
    Uint32 depois = SDL_GetTicks();

    *ms -= (depois - antes);
    if(*ms < 0) *ms = 0;

    return isevt;
}