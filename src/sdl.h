#ifndef __SDL_H__
#define __SDL_H__

#include <SDL2/SDL_image.h>

struct sdl_connector_params 
{
    int window_x;
    int window_y;
    int window_w;
    int window_h;
    int window_flags;
    int renderer_flags;
};

struct sdl_connector 
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    int renderer_flags;
    int window_flags;
    int screen_width;
    int screen_height;
    int screen_mode;
};


struct sdl_connector * sdl_conn__init(struct sdl_connector_params params);
void *                 sdl_conn__free(struct sdl_connector * self);

#endif /* __SDL_H__ */
