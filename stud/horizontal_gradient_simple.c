#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void drawHorizontalGradientBox(SDL_Renderer * renderer,
        const int x, const int y, const int w, const int h, const float steps,
        const SDL_Color c1, const SDL_Color c2, const int fill)
{

    /* Acumulator initial position */
    float yt = y;
    float rt = c1.r;
    float gt = c1.g;
    float bt = c1.b;
    float at = c1.a;
    
    /* Changes in each attribute */
    float ys = h/steps;
    float rs = (c2.r - c1.r)/steps;
    float gs = (c2.g - c1.g)/steps;
    float bs = (c2.b - c1.b)/steps;
    float as = (c2.a - c1.a)/steps;

    for(int i = 0; i < steps ; i++)
    {
        /* Create an horizontal rectangle sliced by the number of steps */
        SDL_Rect rect = { x, yt, w, ys+1 };

        /* Sets the rectangle color based on iteration */
        SDL_SetRenderDrawColor(renderer, rt, gt, bt, at);

        /* Paint it or coverit*/
        if(fill)
            SDL_RenderFillRect(renderer, &rect);
        else
            SDL_RenderDrawRect(renderer, &rect);

        /* Update colors and positions */
        yt += ys;
        rt += rs;
        gt += gs;
        bt += bs;
        at += as;
    }
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("Gradients", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;

    int quit = 0;
    while(!quit)
    {
        while(SDL_PollEvent(&event) != 0)
            if(event.type == SDL_QUIT)
                quit = 1;

        // Draw a ugly background
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 10);
        SDL_RenderClear(renderer);

        drawHorizontalGradientBox(renderer,
            SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4,
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
            100,
            (SDL_Color) { 255, 0, 0, 255 },
            (SDL_Color) { 0, 255, 0, 255 },
            1);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



