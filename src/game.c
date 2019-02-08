#include <stdbool.h>
#include <stdio.h>
#include "ship.h"
#include "game.h"
#include "phys.h"
#include "gameobj.h"
#include "gameobjlist.h"

struct game * 
game__init(struct game_params params)
{
    struct game * self;
    self = malloc(sizeof *self);
    self->num_lives = params.num_lives;

    /* Creates the game object list */
    gameobjlist_st * list = gameobjlist__init();
    self->active_obj = list;

    /* Creates a player ship */
    ship_params_st ship_params = { 
        .size = 1,
        .acceleration = 0,
        .angle = 0,
        .ang_velocity = 0,
        .active = false,
        .life_timer = 0,
        .type = 0,
        .active_bullet_count = 0,
        .shot_power_level = 0,
        .invincibility_timer = 0
    };
    struct ship * ship = ship__init(ship_params);
    self->ship = ship;
    self->ship->active = true;

    /* Assigns the ship to the list of active objects */
    gameobjlist__add(self->active_obj,(struct gameobj *) self->ship);

    return self;
}

void
game__free(struct game * self)
{
    ship__free(self->ship);
    // human_control__free
    // ai_control__free
    // gameobjlist__free(self->active_obj);
    free(self);
}


void
game__increment_score(struct game * self, int value) 
{
    self->score += value;
}

void game__blit(struct game * self)
{
    SDL_RenderPresent(self->sdlconn->renderer);
}


void
game__wait(struct game *self, int wait)
{
    SDL_Delay(wait);
}

