#include <SDL2/SDL.h>
#include <stdio.h>

#define TEMPO_MAXIMO 250

typedef struct {
    Uint32 ultimo_clique;
    int contagem_cliques;
    int esperando;
} EstadoClique;

int AUX_WaitEventTimeoutCount(SDL_Event* evt, int* ms){
    Uint32 antes = SDL_GetTicks();
    int isevt = SDL_WaitEventTimeout(evt, *ms);
    Uint32 depois = SDL_GetTicks();
    *ms -= (depois - antes);
    if(*ms < 0) *ms = 0;
    return isevt;
}

void tratar_clique(EstadoClique *estado, int x, int y) {
    Uint32 agora = SDL_GetTicks();

    if (!estado->esperando || (agora - estado->ultimo_clique > TEMPO_MAXIMO)) {
        estado->contagem_cliques = 1;
        estado->esperando = 1;
    } else {
        estado->contagem_cliques++;
    }

    estado->ultimo_clique = agora;
}

void verificar_timeout_emitir(EstadoClique *estado) {
    if (estado->esperando) {
        Uint32 agora = SDL_GetTicks();
        if (agora - estado->ultimo_clique > TEMPO_MAXIMO) {
            SDL_Event evt;
            SDL_memset(&evt, 0, sizeof(evt));
            evt.type = SDL_USEREVENT;
            evt.user.code = estado->contagem_cliques;
            SDL_PushEvent(&evt);

            estado->esperando = 0;
            estado->contagem_cliques = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *janela = SDL_CreateWindow("2.1",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, 0);

    SDL_Renderer *ren = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    EstadoClique estado_clique = {0, 0, 0};
    SDL_Event evt;
    int espera = 25;
    int amarelo = 1; 

    while (!SDL_QuitRequested()) {
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (isevt) {
             if (evt.type == SDL_MOUSEBUTTONDOWN) {
                tratar_clique(&estado_clique, evt.button.x, evt.button.y);
            } else if (evt.type == SDL_USEREVENT) {
                if (evt.user.code == 2) {
                    if (amarelo) {
                        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0x00, 0xFF); 
                        amarelo = 0;
                    } else {
                        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF); 
                        amarelo = 1;
                    }
                    SDL_RenderClear(ren);
                    SDL_RenderPresent(ren);
                } else if (evt.user.code == 3) {
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); 
                    SDL_RenderClear(ren);

                    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                    int cx = 320, cy = 240, r = 100;
                    for (int w = -r; w <= r; w++) {
                        for (int h = -r; h <= r; h++) {
                            if (w*w + h*h <= r*r) {
                                SDL_RenderDrawPoint(ren, cx + w, cy + h);
                            }
                        }
                    }

                    SDL_RenderPresent(ren);
                }
            }
        }

        if (espera == 0) {
            verificar_timeout_emitir(&estado_clique);
            espera = 25;
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(janela);
    SDL_Quit();
    return 0;
}

