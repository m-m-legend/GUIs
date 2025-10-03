#include <SDL2/SDL.h>
#include <stdio.h>

#define ESC 27

typedef enum { IDLE, PRESSED, DRAGGING, CLICKED, ABORTED } Estado;
Estado estado = IDLE;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int x = 100, y = 100, tamanho = 80;
int offsetX, offsetY;
int originalX, originalY;

int AUX_WaitEventTimeoutCount(SDL_Event* evt, int* ms) {
    Uint32 antes = SDL_GetTicks();
    int isevt = SDL_WaitEventTimeout(evt, *ms);
    Uint32 depois = SDL_GetTicks();
    *ms -= (depois - antes);
    if(*ms < 0) *ms = 0;
    return isevt;
}

void quadrado() {
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); 
    SDL_RenderClear(ren);

    SDL_Rect r = {x, y, tamanho, tamanho};
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); 
    SDL_RenderFillRect(ren, &r);

    SDL_RenderPresent(ren);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro SDL: %s\n", SDL_GetError());
        return 1;
    }

    win = SDL_CreateWindow("2.2",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              600, 600, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event evt;
    int espera = 100; 

    quadrado();

    while (!SDL_QuitRequested()) {
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if(isevt){
            switch (evt.type) {
            case SDL_KEYDOWN:
                if (evt.key.keysym.sym == SDLK_ESCAPE &&
                    (estado == PRESSED || estado == DRAGGING)) {
                    estado = ABORTED;
                    x = originalX;
                    y = originalY;
                    printf("Acao abortada com ESC\n");
                    quadrado();
                    estado = IDLE;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (evt.button.button == SDL_BUTTON_LEFT) {
                    int mx = evt.button.x;
                    int my = evt.button.y;
                    if (mx >= x && mx <= x + tamanho &&
                        my >= y && my <= y + tamanho) {
                        estado = PRESSED;
                        offsetX = mx - x;
                        offsetY = my - y;
                        originalX = x;
                        originalY = y;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (evt.button.button == SDL_BUTTON_LEFT) {
                    if (estado == PRESSED) {
                        estado = CLICKED;
                        printf("Clique detectado!\n");
                    } else if (estado == DRAGGING) {
                        printf("Arrasto finalizado!\n");
                    }
                    estado = IDLE;
                }
                break;

            case SDL_MOUSEMOTION:
                if (estado == PRESSED || estado == DRAGGING) {
                    estado = DRAGGING;
                    x = evt.motion.x - offsetX;
                    y = evt.motion.y - offsetY;
                    quadrado();
                }
                break;
            }
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
