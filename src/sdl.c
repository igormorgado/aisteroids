#include "sdl.h"


struct sdl_connector * 
sdl_conn__init(struct sdl_connector_params params)
{
    struct sdl_connector * self;
    self = malloc(sizeof *self);

    self->renderer_flags = params.renderer_flags;
    self->window_flags = params.window_flags;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    self->screen_width  = params.window_w;
    self->screen_height = params.window_h;
    self->window_flags = params.window_flags;
    self->window = SDL_CreateWindow("AIsterorids",
                                    params.window_x,
                                    params.window_y,
                                    self->screen_width,
                                    self->screen_height,
                                    self->window_flags);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    self->renderer_flags = params.renderer_flags;
    self->renderer = SDL_CreateRenderer(self->window, -1, self->renderer_flags);

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_ShowCursor(0);

    return self;
}


void
sdl_conn__free(struct sdl_connector * self)
{
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    free(self);
    IMG_Quit();
    SDL_Quit();
}

