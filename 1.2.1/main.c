#include <SDL2/SDL.h>

int main(int argc, char* args[]){
    
    /*INICIALIZACAO*/
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.2.1",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        400, 200, SDL_WINDOW_SHOWN
    );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /*EXECUCAO*/
    SDL_SetRenderDrawColor(ren, 135,206,250,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_Rect mar = {0,60,400,200};
    SDL_RenderFillRect(ren, &mar);
    SDL_SetRenderDrawColor(ren, 139,69,19,0x00);
    SDL_Rect barco = {50,30,50,30};
    SDL_RenderFillRect(ren, &barco);
    SDL_SetRenderDrawColor(ren, 27,30,35,0x00);
    SDL_RenderDrawLine(ren, 50,30,50,10);
    SDL_Rect bandeira = {50,8,15,15};
    SDL_RenderFillRect(ren, &bandeira);
    SDL_RenderDrawPoint(ren, 60,45);
    SDL_RenderDrawPoint(ren, 70,45);
    SDL_RenderDrawPoint(ren, 80,45);
    SDL_RenderDrawPoint(ren, 90,45);
    SDL_RenderPresent(ren);
    SDL_Delay(7000);

    /*FINALIZACAO*/
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();





    

}
