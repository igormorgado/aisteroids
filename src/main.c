#include "main.h"
#include "game.h"
#include "sdl.h"
#include "tests.h"
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

    struct game_params game_params = {
        .num_lives = 3
    };

    struct game * game = game__init(game_params);

    // Connects initialized SDL subsystem to the game
    game->sdlconn = sdlconn;

    background__draw(game);
    tests__run();
    game__blit(game);
    game__wait(game, 1000);

    game__free(game);
    sdl_conn__free(sdlconn);

    return 0;
}
