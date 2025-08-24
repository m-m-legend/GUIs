#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h> 


void canhao(SDL_Renderer* ren,int x, int y){
    //Circulo cinza
    filledCircleRGBA(ren, x, y, 5, 0x2C, 0x33, 0x33, 255);
    //Circulo preto
    filledCircleRGBA(ren, x, y, 2, 27, 30, 35, 255);
}

void ondas(SDL_Renderer* ren, int largura, int y_base) {
    SDL_SetRenderDrawColor(ren, 0, 100, 255, 255); 
    for (int x = 0; x < largura; x++) {
        int y = y_base + (int)(10 * sin(x * 0.05)); // amplitude 10px + frequência baixa 
        SDL_RenderDrawPoint(ren, x, y);
    }
}


void mar(SDL_Renderer* ren, int largura, int altura, int y_inicio) {
    for (int i = 0; i < altura; i++) {
        int cor = 200 - i/3; // variação de cor
        SDL_SetRenderDrawColor(ren, 0, 0, cor, 255);
        SDL_RenderDrawLine(ren, 0, y_inicio + i, largura, y_inicio + i);
    }
}


void nuvem(SDL_Renderer* ren, int x, int y, int escala) {
    // Nuvem 
    filledCircleRGBA(ren, x, y, escala, 255, 255, 255, 255);
    filledCircleRGBA(ren, x + escala, y, escala + 5, 255, 255, 255, 255);
    filledCircleRGBA(ren, x + 2*escala, y, escala, 255, 255, 255, 255);
    filledCircleRGBA(ren, x + escala, y - escala/2, escala, 255, 255, 255, 255);
}


void caveira(SDL_Renderer* ren, int x, int y, int w, int h){
    // Centro da bandeira 
    int cx = x + w/2;
    int cy = y + h/2;

    // Escala 
    int raioCabeca = (w < h ? w : h) / 3; 

    // Cabeça 
    filledCircleRGBA(ren, cx, cy, raioCabeca, 255, 255, 255, 255);

    // Olhos
    int olhoOffsetX = raioCabeca / 2;
    int olhoOffsetY = raioCabeca / 3;
    int olhoRaio = raioCabeca / 4;
    filledCircleRGBA(ren, cx - olhoOffsetX, cy - olhoOffsetY, olhoRaio, 0, 0, 0, 255);
    filledCircleRGBA(ren, cx + olhoOffsetX, cy - olhoOffsetY, olhoRaio, 0, 0, 0, 255);
    filledCircleRGBA(ren, cx - olhoOffsetX, cy - olhoOffsetY, olhoRaio-1, 0xC3, 0x00, 0x10, 255);
    filledCircleRGBA(ren, cx + olhoOffsetX, cy - olhoOffsetY, olhoRaio-1, 0xC3, 0x00, 0x10, 255);

    // Nariz 
    int narizAltura = raioCabeca / 2;
    filledTrigonRGBA(ren,
                     cx - olhoRaio/2, cy, 
                     cx + olhoRaio/2, cy, 
                     cx, cy + narizAltura,
                     0, 0, 0, 255);

    // Dentes 
    int baseY = cy + raioCabeca/2;
    for (int i = -raioCabeca/2; i <= raioCabeca/2; i += olhoRaio){
        lineRGBA(ren, cx + i, baseY, cx + i, baseY + olhoRaio, 0x2C, 0x33, 0x33, 255);
    }

    // Ossos cruzados 
    int ossoComprimento = raioCabeca * 1.4;
    thickLineRGBA(ren, cx - ossoComprimento, cy - ossoComprimento,
                       cx + ossoComprimento, cy + ossoComprimento,
                       3, 255, 255, 255, 255);
    thickLineRGBA(ren, cx - ossoComprimento, cy + ossoComprimento,
                       cx + ossoComprimento, cy - ossoComprimento,
                       3, 255, 255, 255, 255);
    
}


int main(int argc, char* args[]){
    
    /*INICIALIZACAO*/
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.2.2",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED
    );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /*EXECUCAO*/
    SDL_SetRenderDrawColor(ren, 135, 206, 250, 255); 
    SDL_RenderClear(ren);
    mar(ren, 800, 180, 420);
    for(int i = 430;i<=590;i+=20){
        ondas(ren, 800, i);
    }
    SDL_SetRenderDrawColor(ren, 139,69,19,0x00);
    SDL_Rect barco = {50,370,100,50};
    SDL_RenderFillRect(ren, &barco);
    SDL_SetRenderDrawColor(ren, 27,30,35,0x00);
    SDL_RenderDrawLine(ren, 50,370,50,350);
    SDL_Rect bandeira = {50,300,50,50};
    SDL_RenderFillRect(ren, &bandeira);
    filledCircleRGBA(ren, 550, 45, 20, 255, 215, 0, 255);
    nuvem(ren, 200, 100, 20);
    nuvem(ren, 400, 80, 25);
    nuvem(ren, 650, 120, 15);
    SDL_SetRenderDrawColor(ren, 27,30,35,0x00);
    SDL_RenderDrawPoint(ren, 55,395);
    canhao(ren, 65, 395);
    canhao(ren, 85, 395);
    SDL_RenderDrawPoint(ren, 95,395);
    canhao(ren, 105, 395);
    canhao(ren, 125, 395);
    SDL_RenderDrawPoint(ren, 145,395);
    caveira(ren, bandeira.x, bandeira.y, bandeira.w, bandeira.h);
    SDL_RenderPresent(ren);
    SDL_Delay(10000);

    /*FINALIZACAO*/
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();





    

}
