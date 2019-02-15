#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gameobj.h"
#include "phys.h"
#include "common.h"


struct gameobj *
gameobj__init(const struct gameobj_params params)
{
	struct gameobj * self;
	self = smalloc(sizeof *self);

	self->size = params.size;

	struct point3f * axis;
	axis = smalloc(sizeof *axis);
	memset(axis, 0, sizeof *axis);
	self->axis = axis;

	/* TODO:
	 * Instead a pointer should we use the direct reference as
	 * struct point position
	 */
	struct point3f * position;
	position = smalloc(sizeof *position);
	memset(position, 0, sizeof *position);
	self->position = position;

	struct point3f * velocity;
	velocity = smalloc(sizeof *velocity);
	memset(velocity, 0, sizeof *velocity);
	self->velocity = velocity;

	self->acceleration = params.acceleration;

	self->angle = params.angle;
	self->ang_velocity = params.ang_velocity;

	struct sphere3f * bound_sphere;
	bound_sphere = smalloc(sizeof *bound_sphere);
	memset(bound_sphere, 0, sizeof *bound_sphere);
	self->bound_sphere = bound_sphere;

	self->active = params.active;
	self->life_timer = params.life_timer;
	self->type = params.type;
	self->obj_flags = OBJ_RESET;

	return self;
}


void 
gameobj__free(struct gameobj * self)
{
	sfree(self->bound_sphere);
	sfree(self->velocity);
	sfree(self->position);
	sfree(self->axis);
	sfree(self);
}


void
gameobj__update(struct gameobj * self, float dt)
{
	accelerate(self->velocity, self->acceleration, dt);
	move(self->position, self->velocity, dt);
	rotate(&(self->angle), self->ang_velocity, dt);

	self->position->z = 0.0f;

	if((self->obj_flags & OBJ_NOTIMER) == 0) {
		self->life_timer -= dt;
		if(self->life_timer < 0.0f) {
			self->active = false;
		}
	}
}

char *
gameobj__fmt(const struct gameobj * self)
{
	const size_t tsize = 100;
	char * pos = point3f_fmt(self->position);
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
	unit_vector(self->velocity, unit);
}
