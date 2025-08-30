#include <SDL2/SDL.h>

int main(int argc, char** args){
    
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.4.1",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        200, 100, SDL_WINDOW_SHOWN
    );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUCAO */

    SDL_Rect r = {40,20,10,10};
    SDL_Event evt;

    SDL_Rect mouseRects[10];
    SDL_Color mouseColors[10];
    int rectCount = 0;

    while(!SDL_QuitRequested()){
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        for(int i = 0; i<rectCount; i++){
            SDL_SetRenderDrawColor(ren, mouseColors[i].r, mouseColors[i].g, mouseColors[i].b, mouseColors[i].a);
            SDL_RenderFillRect(ren, &mouseRects[i]);
        }
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);

        SDL_WaitEvent(&evt);
        if(evt.type == SDL_KEYDOWN){
            switch(evt.key.keysym.sym){
                case SDLK_UP:
                    r.y -= 5;
                    break;
                case SDLK_DOWN:
                    r.y += 5;
                    break;
                case SDLK_LEFT:
                    r.x -= 5;
                    break;
                case SDLK_RIGHT:
                    r.x += 5;
                    break;
            }
            if (r.x < 0) r.x = 0;
            if (r.y < 0) r.y = 0;
            if (r.x > 200 - r.w) r.x = 200 - r.w;
            if (r.y > 100 - r.h) r.y = 100 - r.h;
        } else if(evt.type == SDL_MOUSEBUTTONDOWN && rectCount<10){
            int x = evt.button.x;
            int y = evt.button.y;
            SDL_Rect newRect = {x,y,20,10};
            SDL_Color color = {x%256, y%256, (x+y)%256, 255}; //para não ultrapassar 255
            mouseRects[rectCount] = newRect;
            mouseColors[rectCount] = color;
            rectCount++;
        }

    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();



    
    return 0;
}