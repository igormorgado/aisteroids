#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>

const int MAX_SHIPS = 100;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
typedef float triangle[3][2];

void rotate( float angle,  float srcx,  float srcy, float * dstx, float * dsty) 
{
   *dstx = srcx * cos(angle) - srcy * sin(angle);
   *dsty = srcx * sin(angle) + srcy * cos(angle);
}

void scale( float ratio,  float srcx, float srcy, float * dstx, float * dsty) 
{
   *dstx = ratio * srcx;
   *dsty = ratio * srcy;
}

void translate( float x,  float y, float srcx,  float srcy, float * dstx, float * dsty)
{
   *dstx = srcx + x;
   *dsty = srcy + y;
}

char * ship_fmt(triangle t) 
{
    char * s;
    const int nsize = 6;
    const int vsize = 8;
    const int fsize = 4;
    const int tsize = 10 + (nsize * vsize);
    s = malloc(tsize+1);
    snprintf(s, tsize, "(%*.*f,%*.*f)(%*.*f,%*.*f)(%*.*f,%*.*f)",
            vsize, fsize, t[0][0], 
            vsize, fsize, t[0][1],
            vsize, fsize, t[1][0], 
            vsize, fsize, t[1][1],
            vsize, fsize, t[2][0],
            vsize, fsize, t[2][1]);

    return s;
}

void drawship(SDL_Renderer *renderer, triangle ship, float x, float y, float angle, float zoom, int r, int  g, int b, int a)
{
    triangle mship, tship;

    // Centering
    float rx = (ship[0][0] + ship[1][0])/2;
    float ry = (ship[0][1] + ship[2][1])/2;

    memcpy(&mship, ship, sizeof(triangle));
    // printf("ISHIP %s\n", ship_fmt(mship));

    // Translate to ship center
    for(int i=0; i<3; i++)
        translate(-rx, -ry, mship[i][0], mship[i][1], &tship[i][0], &tship[i][1]);
    memcpy(&mship, &tship, sizeof(triangle));

    // printf("CSHIP %s\n", ship_fmt(mship));

    // Rotate
    for(int i=0; i<3; i++)
        rotate(angle, mship[i][0], mship[i][1], &tship[i][0], &tship[i][1]);
    memcpy(&mship, &tship, sizeof(triangle));

    // printf("RSHIP %s\n", ship_fmt(mship));
 
    //Scale
    for(int i=0; i<3; i++)
        scale(zoom, mship[i][0], mship[i][1], &tship[i][0], &tship[i][1]);
    memcpy(&mship, &tship, sizeof(triangle));

    // printf("SSHIP %s\n", ship_fmt(mship));
    
    // Translate to ship origin 
    for(int i=0; i<3; i++)
        translate(rx, ry, mship[i][0], mship[i][1], &tship[i][0], &tship[i][1]);
    memcpy(&mship, &tship, sizeof(triangle));

    // printf("OSHIP %s\n", ship_fmt(mship));

    
    // Translate to ship on screen
    for(int i=0; i<3; i++)
        translate(x, y, mship[i][0], mship[i][1], &tship[i][0], &tship[i][1]);
    memcpy(&mship, &tship, sizeof(triangle));

    // printf("PSHIP %s\n", ship_fmt(mship));

    aatrigonRGBA(renderer, 
            mship[0][0], mship[0][1],
            mship[1][0], mship[1][1],
            mship[2][0], mship[2][1],
            r, g, b, a);

    // printf("\n");
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
    float x[MAX_SHIPS];
    float y[MAX_SHIPS];
    float angle[MAX_SHIPS];
    float scale[MAX_SHIPS];
    float angvel[MAX_SHIPS];
    float r[MAX_SHIPS];
    float g[MAX_SHIPS];
    float b[MAX_SHIPS];

    // x pos
    for(int i = 0; i< MAX_SHIPS; i++)
    {
        x[i] = rand()%SCREEN_WIDTH;
        y[i] = rand()%SCREEN_HEIGHT;
        angle[i] = (rand()%360) * (M_PI/180);
        scale[i] = rand()%10 + 10;
        angvel[i] = rand()%10 / 10. + .2;
        r[i] = rand()/255;
        g[i] = rand()/255;
        b[i] = rand()/255;
    }

    // Unzado
    //triangle ship = { { 0.0f, -1.0f }, { 1.0f, 0.0f}, { 0.0f, 1.0f} };
    // Equilatero
    //triangle ship = { { 0.0f, 0.0f }, { (sqrt(3)/2), 0.5f}, { 0.0f, 1.0f} };
    // Isosceles
    triangle ship = { { 0.0f, 0.0f }, { 2.0f, 0.5f}, { 0.0f, 1.0f} };

    while(!quit)
    {
        while(SDL_PollEvent(&event) != 0)
            if(event.type == SDL_QUIT)
                quit = 1;

        // Draw a ugly background
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 10);
        SDL_RenderClear(renderer);

        for(int i = 0; i < MAX_SHIPS; i++)
        {
            drawship(renderer, ship, x[i], y[i], angle[i], scale[i], r[i], g[i], b[i], 255);
            angle[i] += angvel[i] * (M_PI/180);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



