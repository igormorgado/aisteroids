#include "main.h"
#include "game.h"
#include "sdl.h"
#include "background.h"

int
main(void)
{
    struct sdl_connector_params conn_params = {
        .window_x = SDL_WINDOWPOS_UNDEFINED,
        .window_y = SDL_WINDOWPOS_UNDEFINED,
        .window_w = 1024,
        .window_h = 768,
        .window_flags = 0,
        .renderer_flags = SDL_RENDERER_ACCELERATED };

    struct sdl_connector * sdlconn = sdl_conn__init(conn_params);

    struct game * game = game__init();

    // Connects initialized SDL subsystem to the game
    game->sdlconn = sdlconn;

    background__draw(game);
    game__update(game, 0.01);
    game__blit(game);
    game__wait(game, 1000);

    game = game__free(game);
    sdlconn = sdl_conn__free(sdlconn);

    return 0;
}
