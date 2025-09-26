#include <SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, int* ms){
    Uint32 antes = SDL_GetTicks();
    int isevt = SDL_WaitEventTimeout(evt, *ms);
    Uint32 depois = SDL_GetTicks();

    *ms -= (depois - antes);
    if(*ms < 0) *ms = 0;

    return isevt;
}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.5.3",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         300, 200, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Rect r = {40, 40, 10, 10};

    const int x0 = 40, y0 = 40;
    const int largura = 120, altura = 80;

    SDL_Rect portaDireita = { x0 + largura - 1, y0 + 30, 2, 20 };
    SDL_Rect portaBaixo   = { x0 + 50, y0 + altura - 1, 20, 2 };

    int estadoPortaDireita = 0;
    int estadoPortaBaixo   = 0;

    SDL_Event evt;
    int espera = 25;

    while (!SDL_QuitRequested()) {
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if(isevt){
            if (evt.type == SDL_MOUSEBUTTONDOWN) {
                if (evt.button.x >= portaDireita.x && evt.button.x < portaDireita.x + portaDireita.w &&
                    evt.button.y >= portaDireita.y && evt.button.y < portaDireita.y + portaDireita.h) {
                    estadoPortaDireita = !estadoPortaDireita;
                }
                if (evt.button.x >= portaBaixo.x && evt.button.x < portaBaixo.x + portaBaixo.w &&
                    evt.button.y >= portaBaixo.y && evt.button.y < portaBaixo.y + portaBaixo.h) {
                    estadoPortaBaixo = !estadoPortaBaixo;
                }
            }
        }
    

        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_DOWN])  r.y += 1;
        if (state[SDL_SCANCODE_UP])    r.y -= 1;
        if (state[SDL_SCANCODE_LEFT])  r.x -= 1;
        if (state[SDL_SCANCODE_RIGHT]) r.x += 1;

        if (r.x < 0) r.x = 0;
        if (r.y < 0) r.y = 0;
        if (r.x > 300 - r.w) r.x = 300 - r.w;
        if (r.y > 200 - r.h) r.y = 200 - r.h;

        int dentroComodo = (r.x + r.w > x0 && r.x < x0 + largura && r.y + r.h > y0 && r.y < y0 + altura);

        if (dentroComodo) {
            if (r.x < x0) {
                r.x = x0;
            }
            if (r.y < y0) {
                r.y = y0;
            }
            if (r.x + r.w > x0 + largura) {
                if (!estadoPortaDireita || !(r.y + r.h > portaDireita.y && r.y < portaDireita.y + portaDireita.h)) {
                    r.x = x0 + largura - r.w;
                }
            }
            if (r.y + r.h > y0 + altura) {
                if (!estadoPortaBaixo || !(r.x + r.w > portaBaixo.x && r.x < portaBaixo.x + portaBaixo.w)) {
                    r.y = y0 + altura - r.h;
                }
            }
        }
        
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 27,30,35,0x00);
        SDL_Rect comodo = { x0, y0, largura, altura };
        SDL_RenderDrawRect(ren, &comodo);

        SDL_SetRenderDrawColor(ren, 255,0,0,0x00);
        SDL_RenderFillRect(ren, &r);

        SDL_SetRenderDrawColor(ren, estadoPortaDireita ? 0 : 255,0,estadoPortaDireita ? 255 : 215,0);
        SDL_RenderFillRect(ren, &portaDireita);

        SDL_SetRenderDrawColor(ren, estadoPortaBaixo ? 0 : 255,0,estadoPortaBaixo ? 255 : 215,0);
        SDL_RenderFillRect(ren, &portaBaixo);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}