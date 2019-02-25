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
	memset(self, 0, sizeof *self);

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

struct gameobj *
game__check_collision(struct gameobj * pobj, struct gameobjlist * list)
{
	struct gameobj * pobjcol = NULL;
	struct gameobjnode * pnode = NULL;

	pnode = list->front;
	while(pnode) {
		pobjcol = pnode->obj;
		if(pobj == pobjcol)
			continue;
		if(pobj->is_colliding(pobj, pobjcol) == true)
			return pobjcol;

		pnode = pnode->next;
	}
	return NULL;
}

void
game__update(struct game *self, float dt)
{
	struct gameobj * pobj = NULL;
	struct gameobj * pobjcol = NULL;
	struct gameobjnode * pnode = NULL;

	if (self) {
		pnode = self->active_obj->front;
	}

	if(pnode->obj) {
		pobj = pnode->obj;
	}

	while(pobj)
	{
		// If object active  update positions
		if(pobj->active == true) {
			pobj->update(pobj, dt);
		} else {
			continue;
		}

		// Check if `pobj` coliding with any other game obj?
		if((pobj->obj_flags & OBJ_NONE) == 0) {
			pobjcol = game__check_collision(pobj, self->active_obj);
		}
		
		// If `pobj` colided with `poblcol`, do proper actions
		if(pobjcol) {
			pobj->explode();
			pobj->do_collision(pobjcol);
			pobjcol = NULL;
		}
		
		pnode = pnode->next;
		if (pnode) {
			pobj = pnode->obj;
		}
	}
}
