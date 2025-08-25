#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.3.1",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         300, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = {40, 40, 10, 10};  
    int ciclos = 0;

    // Comodo
    const int x0 = 40, y0 = 40;
    const int largura = 120, altura = 80;

    SDL_Rect portaDireita = { x0 + largura - 1, y0 + 30, 2, 20 };
    SDL_Rect portaBaixo   = { x0 + 50,          y0 + altura - 1, 20, 2 };

    
    int etapa = 0;

    while (ciclos < 2) {
        if (etapa == 0) { 
            int xLim = x0 + largura - r.w;
            if (r.x < xLim) r.x += 1;
            else etapa = 1;
        }
        else if (etapa == 1) { 
            int yAlvo = portaDireita.y+5; 
            if (r.y < yAlvo) r.y += 1;
            else etapa = 2;
        }
        else if (etapa == 2) { 
            int xFora = x0 + largura + 1; 
            if (r.x < xFora) r.x += 1;
            else etapa = 3;
        }
        else if (etapa == 3) { 
            int yAbaixo = y0 + altura + 1; 
            if (r.y < yAbaixo) r.y += 1;
            else etapa = 4;
        }
        else if (etapa == 4) { 
            int xAlvo = portaBaixo.x + (portaBaixo.w - r.w)/2; 
            if (r.x > xAlvo) r.x -= 1;
            else etapa = 5;
        }
        else if (etapa == 5) { 
            int yDentro = y0 + altura - r.h; 
            if (r.y > yDentro) r.y -= 1;
            else etapa = 6;
        }
        else if (etapa == 6) { 
            if (r.x > x0) r.x -= 1;
            else etapa = 7;
        }
        else if (etapa == 7) { 
            if (r.y > y0) r.y -= 1;
            else { etapa = 0; ciclos++; }
        }

        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 27,30,35, 0x00);
        SDL_Rect comodo = { x0, y0, largura, altura };
        SDL_RenderDrawRect(ren, &comodo);

        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderFillRect(ren, &portaDireita);
        SDL_RenderFillRect(ren, &portaBaixo);

        SDL_SetRenderDrawColor(ren, 255, 215, 0, 0x00);
        SDL_RenderDrawRect(ren, &portaDireita);
        SDL_RenderDrawRect(ren, &portaBaixo);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 0x00);
        SDL_RenderFillRect(ren, &r);

        SDL_RenderPresent(ren);

        // 10 px/s → 1 px por iteração + 100 ms por frame
        SDL_Delay(100);
    }

    /* FINALIZAÇÃO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
