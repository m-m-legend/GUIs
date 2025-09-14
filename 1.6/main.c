#include <SDL2/SDL.h>
#include <stdbool.h>

enum{
    NENHUM = 0,
    AZUL,
    AMARELO,
    VERDE
};

int AUX_WaitEventTimeoutCount(SDL_Event* evt, int* ms){
    Uint32 antes = SDL_GetTicks();
    int isevt = SDL_WaitEventTimeout(evt, *ms);
    Uint32 depois = SDL_GetTicks();

    *ms -= (depois - antes);
    if(*ms < 0) *ms = 0;

    return isevt;
}

void reset_corrida(SDL_Rect* r, SDL_Rect* t, SDL_Rect* l,
                   bool* r_chegou, bool* l_chegou, bool* t_chegou,
                   int* vencedor, int* espera) {
    *r = (SDL_Rect){20,20,20,10};
    *t = (SDL_Rect){20,40,20,10};
    *l = (SDL_Rect){20,60,20,10};
    *r_chegou = false;
    *l_chegou = false;
    *t_chegou = false;
    *vencedor = NENHUM;
    *espera = 25;
}

int main(int argc, char** args){
    
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.6",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        200, 100, SDL_WINDOW_SHOWN
    );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUCAO */

    SDL_Rect r = {20,20,20,10}; //retangulo pelo teclado
    SDL_Rect t = {20, 40, 20, 10}; //retangulo pelo tempo
    SDL_Rect l = {20,60,20,10}; //retangulo pelo mouse
    SDL_Rect chegada = {180, 0, 10, 100}; //linha de chegada

    SDL_Event evt;

    int espera;
    bool r_chegou; bool l_chegou; bool t_chegou;
    bool final_corrida;
    int vencedor;
    bool resultado = false;

    reset_corrida(&r, &t, &l, &r_chegou, &l_chegou, &t_chegou, &vencedor, &espera);

    while(!SDL_QuitRequested()){
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if(isevt){
            if(evt.type == SDL_KEYDOWN && !r_chegou){
                        switch(evt.key.keysym.sym){
                            case SDLK_RIGHT:
                                r.x += 5;
                                break;
                            case SDLK_LEFT:
                                r.x -= 5;
                                break;
                        }
                        if (r.x < 0) r.x = 0;
                        if (r.y < 0) r.y = 0;
                        if (r.x > 200 - r.w) r.x = 200 - r.w;
                        if (r.y > 100 - r.h) r.y = 100 - r.h;

                        if (r.x + r.w >= chegada.x){  
                            r.x = chegada.x - r.w;
                            r_chegou = true;
                            if(vencedor == NENHUM) vencedor = AZUL;             
                }

                    } else if(evt.type == SDL_MOUSEMOTION && !l_chegou){
                        l.x = evt.motion.x;
                        if (l.x < 0) l.x = 0;
                        if (l.y < 0) l.y = 0;
                        if (l.x > 200 - l.w) l.x = 200 - r.w;
                        if (l.y > 100 - l.h) l.y = 100 - r.h;
                        
                        if (l.x + l.w >= chegada.x){  
                            l.x = chegada.x - l.w;
                            l_chegou = true;
                            if(vencedor == NENHUM) vencedor = VERDE;   
                }

                    }

                    }
        if(espera == 0){
        	t.x += 1;
        	
            if (t.x < 0) t.x = 0;
            if (t.y < 0) t.y = 0;
            if (t.x > 200 - t.w) t.x = 200 - t.w;
            if (t.y > 100 - t.h) t.y = 100 - t.h;
            
            if (t.x + t.w > chegada.x){
                t.x = chegada.x - t.w;
                t_chegou = true;
                if(vencedor == NENHUM) vencedor = AMARELO;
            }    
            
            espera = 25;
        }

        if(r_chegou && l_chegou && t_chegou && !final_corrida){
            final_corrida = true;
        }

        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x03, 0x01, 0x01, 0x00);
        SDL_RenderFillRect(ren, &chegada);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);
        for(int y = -20; y < chegada.h + 20; y += 10){
            SDL_RenderDrawLine(
                ren,
                chegada.x, y,               
                chegada.x + chegada.w, y+20  
            );
        }
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0x00, 0x00);
        SDL_RenderFillRect(ren, &t);
        SDL_SetRenderDrawColor(ren, 0x4A, 0x97, 0x00, 0x00);
        SDL_RenderFillRect(ren, &l);

        
        
        

        
        
        SDL_RenderPresent(ren);
        if (r_chegou && l_chegou && t_chegou && !resultado) {
            const char* msg = NULL;
            switch (vencedor) {
                case AZUL:    msg = "O carro AZUL venceu!"; break;
                case AMARELO: msg = "O carro AMARELO venceu!"; break;
                case VERDE:   msg = "O carro VERDE venceu!"; break;
                default:      msg = "Ninguém venceu."; break;
            }

            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                    "Resultado da Corrida",
                                    msg,
                                    win);
            
            resultado = true;

            reset_corrida(&r, &t, &l, &r_chegou, &l_chegou, &t_chegou, &vencedor, &espera);
            resultado = false;
            }

}
    

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();



    
    return 0;

}
