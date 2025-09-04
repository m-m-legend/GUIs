#include <SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, int* ms){
    Uint32 antes = SDL_GetTicks();
    int isevt = SDL_WaitEventTimeout(evt, *ms);
    Uint32 depois = SDL_GetTicks();

    *ms -= (depois - antes);
    if(*ms < 0) *ms = 0;

    return isevt;
}

int main(int argc, char** args){
    
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.5.1",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        200, 100, SDL_WINDOW_SHOWN
    );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUCAO */

    SDL_Rect r = {20,20,20,10}; //retangulo pelo teclado
    SDL_Rect t = {20, 40, 20, 10}; //retangulo pelo tempo
    SDL_Rect l = {20,60,20,10}; //retangulo pelo mouse

    SDL_Event evt;


    while(!SDL_QuitRequested()){
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &r); 
        SDL_RenderFillRect(ren, &t);
        SDL_RenderFillRect(ren, &l);

        if(t.x > 200 - t.w) t.x = 0;
        if (t.x < 0) t.x = 0;
        if (t.y < 0) t.y = 0;
        if (t.x > 200 - t.w) t.x = 0;
        if (t.y > 100 - t.h) t.y = 0;

        t.x += 1; t.y += 1;
        
        int espera = 7;
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if(isevt){

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
                    } else if(evt.type == SDL_MOUSEMOTION){
                        l.x = evt.motion.x;
                        l.y = evt.motion.y;
                    }

                    } else{
                        espera = 7;
                    }
        
        SDL_RenderPresent(ren);

    }
    

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();



    
    return 0;
}