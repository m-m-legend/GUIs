#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "maquina.h"

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window * win = SDL_CreateWindow("Bellicus", 0, 0, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN | 0x00001000);
	int WIDTH, 
		HEIGHT;
	SDL_GetWindowSize(win, &WIDTH,&HEIGHT);
	int MWIDTH = WIDTH/2, MHEIGHT = HEIGHT/2;
	SDL_Renderer * ren = SDL_CreateRenderer(win, -1, 0);
	SDL_ShowCursor(SDL_DISABLE);
	srand(SDL_GetTicks());
	int apprunning = 1;
	
	while (!SDL_QuitRequested() && apprunning) {
		MenuOption escolha = menu_loop(ren, win, WIDTH, HEIGHT);
		//MENU DO JOGO
		if(escolha == MENU_PLAY){
            //ENTRA NO JOGO
            printf("Jogar!"); 
        } 
        else if (escolha == MENU_TUTORIAL) {
            //TUTORIAL INICIADO
			printf("Tutorial iniciado!");
		} else if (escolha == MENU_CREDITS) {
            //CREDITOS INICIADO
			printf("Bruno, Eraldo e Marcos");
		} else if (escolha == MENU_SAIR) {
            //SAIR
			apprunning = 0;
		}
	}
	
	//finaliza a aplicação
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
