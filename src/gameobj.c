#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "gameobj.h"
#include "phys.h"
#include "common.h"


struct gameobj *
gameobj__init(void)
{
	struct gameobj * self;
	self = smalloc(sizeof *self);
	self->obj_flags = OBJ_RESET;
	return self;
}

void *
gameobj__free(struct gameobj * self)
{
	return sfree(self);
}

void
gameobj__zero(struct gameobj * self)
{
	memset(self, 0, sizeof *self);
}

void
gameobj__update(struct gameobj * self, float dt)
{
	debug_print_gameobj_fmt(self);
	accelerate(&self->velocity, self->acceleration, dt);
	debug_print_gameobj_fmt(self);
	move(&self->position, &self->velocity, dt);
	debug_print_gameobj_fmt(self);
	rotate(&(self->angle), self->ang_velocity, dt);

	debug_print_gameobj_fmt(self);
	self->position.z = 0.0f;

	debug_print_gameobj_fmt(self);
	if((self->obj_flags & OBJ_NOTIMER) == 0) {
		self->life_timer -= dt;
		if(self->life_timer <= 0.0f) {
			self->active = false;
		}
	}
}

/*
 * TODO:
 * Is there anyway to avoid call FREE() on gameobj__fmt caller?
 * Is possible to return a string instead a pointer to char?
 * Because it leaks if forgotten=(
 */
char *
gameobj__fmt(const struct gameobj * self)
{
	const size_t tsize = 100;
	char * pos = point3f_fmt(&self->position);
	char * s = smalloc(tsize + 1);

	snprintf(s, tsize, "Type: %d - Flags: %d - Active: %5s - Pos (%s)\n",
			self->type,
			self->obj_flags,
			self->active ? "true":"false",
			pos
		);
	sfree(pos);
	return s;

}

void
gameobj__print(const struct gameobj * self)
{
	char *gfmt = gameobj__fmt(self);
	printf("%s\n", gfmt);
	sfree(gfmt);
}

// struct point3f *
// gameobj__unit_vector_facing(struct gameobj * self)
// {
//     //Returns the direction unit vector
//     return NULL;
// }

/* Passing the destination vector, makes the caller responsible to allocate
 * and free memory regarding this struct. Is this better approach than
 * return a pointer?
 */
void
gameobj__unit_vector_velocity(struct gameobj * self, struct point3f * unit)
{
	unit_vector(&self->velocity, unit);
}
