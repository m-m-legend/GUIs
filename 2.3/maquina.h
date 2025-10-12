#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#ifndef MAQUINA_H

typedef enum {
    MENU_PLAY,
    MENU_TUTORIAL,
    MENU_CREDITS,
    MENU_SAIR,
    MENU_TOTAL
} MenuOption;

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32 * ms);

#endif
