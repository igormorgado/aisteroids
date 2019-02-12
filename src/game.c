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
    struct gameobjlist * list = gameobjlist__init();
    self->active_obj = list;

    /* Creates a player ship */
    struct ship_params ship_params = { 
        .base.size = 1,
        .base.acceleration = 0,
        .base.angle = 0,
        .base.ang_velocity = 0,
        .base.active = false,
        .base.life_timer = 0,
        .base.type = 0,
        .active_bullet_count = 0,
        .shot_power_level = 0,
        .invincibility_timer = 0
    };
    struct ship * ship = ship__init(ship_params);
    self->main_ship = ship;
    self->main_ship->base.active = true;

    /* Assigns the ship to the list of active objects */
    gameobjlist__add(self->active_obj,(struct gameobj *) self->main_ship);

    return self;
}

void
game__free(struct game * self)
{
    ship__free(self->main_ship);
    // human_control__free
    // ai_control__free
    // gameobjlist__free(self->active_obj);
    free(self);
}

void game__blit(struct game * self)
{
    SDL_RenderPresent(self->sdlconn->renderer);
}

void
game__update_score(struct game *self)
{
    self->score = self->main_ship->score;

    if (self->score > self->highscore)
        self->highscore = self->score;
}

void
game__reset_score(struct game *self)
{
    self->score = 0;
}


void
game__wait(struct game *self, int wait)
{
    SDL_Delay(wait);
}


void
game__update(struct game *self, float dt)
{
  struct gameobjlist * list1 = gameobjlist__init();

  gameobjlist__free(list1);
}
