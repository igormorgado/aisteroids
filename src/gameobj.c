#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "gameobj.h"
#include "phys.h"
#include "common.h"


struct gameobj *
gameobj__init(struct gameobj_params params)
{
    struct gameobj * self;
    self = smalloc(sizeof *self);

    self->size = params.size;

    struct point3f * axis;
    axis = smalloc(sizeof *axis);
    self->axis = axis;

    /* TODO:
     * Instead a pointer should we use the direct reference as
     * struct point position
     */
    struct point3f * position;
    position = smalloc(sizeof *position);
    self->position = position;

    struct point3f * velocity;
    velocity = smalloc(sizeof *velocity);
    self->velocity = velocity;

    self->acceleration = params.acceleration;

    self->angle = params.angle;
    self->ang_velocity = params.ang_velocity;

    struct sphere3f * bound_sphere;
    bound_sphere = smalloc(sizeof *bound_sphere);
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

    if((self->obj_flags & OBJ_NOTIMER) == 0)
    {
        self->life_timer -= dt;
        if(self->life_timer < 0.0f) {
            self->active = false;
        }
    }
}

void
gameobj__print(struct gameobj * self)
{
	char *sfmt = point3f_fmt(self->position);
	printf("Type: %d - Flags: %d -  Active: %5s - Pos (%s)\n",
	        self->type,
	        self->obj_flags,
	        self->active ? "true":"false",
		sfmt
	);
	sfree(sfmt);
}



// struct point3f *
// gameobj__unit_vector_facing(struct gameobj * self)
// {
//     //Returns the direction unit vector
//     return NULL;
// }


// struct point3f *
// gameobj__unit_vector_velocity(struct gameobj * self)
// {
//     //Returns the velocity unit vector
//     return NULL;
// }
