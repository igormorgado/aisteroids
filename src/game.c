#include <stdbool.h>
#include <stdio.h>
#include "ship.h"
#include "game.h"
#include "phys.h"
#include "gameobj.h"
#include "gameobjlist.h"
#include "common.h" 

struct game * 
game__init(void)
{
	struct game * self;
	self = smalloc(sizeof *self);

	/* Creates the game object list */
	struct gameobjlist * list = gameobjlist__init();
	self->active_obj = list;

	/* Creates a player ship */
	struct ship * ship = ship__init();
	ship->base.size = 1;
	ship->base.active = true;

	self->main_ship = ship;

	/* Assigns the ship to the list of active objects */
	gameobjlist__push_front(self->active_obj,(struct gameobj *) self->main_ship);

	return self;
}

void *
game__free(struct game * self)
{
	ship__free(self->main_ship);
	// human_control__free
	// ai_control__free
	// gameobjlist__free(self->active_obj);
	return sfree(self);
}

void 
game__blit(struct game * self)
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
