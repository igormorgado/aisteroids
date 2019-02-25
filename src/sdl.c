#include "sdl.h"
#include "common.h"

#define SET_PARAM(PARAM, DEFAULT)			\
	if(params.PARAM)				\
		self->PARAM = params.PARAM;		\
	else						\
		self->PARAM = DEFAULT;


struct sdl_connector * 
sdl_conn__init(struct sdl_connector_params params)
{
    struct sdl_connector * self;
    self = smalloc(sizeof *self);
    memset(self, 0, sizeof *self);

    SET_PARAM(renderer_flags, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SET_PARAM(window_flags, SDL_WINDOW_SHOWN);
    SET_PARAM(window_w, 0);
    SET_PARAM(window_h, 0);
    SET_PARAM(window_x, SDL_WINDOWPOS_CENTERED);
    SET_PARAM(window_y, SDL_WINDOWPOS_CENTERED);

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    self->window = SDL_CreateWindow("AIsterorids",
                                    self->window_x,
                                    self->window_y,
                                    self->window_w,
                                    self->window_h,
                                    self->window_flags);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    self->renderer = SDL_CreateRenderer(self->window, -1, self->renderer_flags);

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_ShowCursor(0);

    return self;
}


void *
sdl_conn__free(struct sdl_connector * self)
{
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    sfree(self);
    IMG_Quit();
    SDL_Quit();
    return NULL;
}

