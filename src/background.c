#include "background.h"

#include <SDL2/SDL_image.h>

void 
background__draw(struct game *game)
{
    SDL_SetRenderDrawColor(game->sdlconn->renderer, 96, 128, 255, 255);
    SDL_RenderClear(game->sdlconn->renderer);
}

