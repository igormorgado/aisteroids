#include <stdbool.h>
#include <stdlib.h>

#include "gameobj.h"
#include "phys.h"


struct gameobj *
gameobj__init(struct gameobj_params params)
{
    struct gameobj * self;
    self = malloc(sizeof *self);

    self->size = params.size;

    point3f_st * axis;
    axis = malloc(sizeof *axis);
    self->axis = axis;

    point3f_st * position;
    position = malloc(sizeof *position);
    self->position = position;

    point3f_st * velocity;
    velocity = malloc(sizeof *velocity);
    self->velocity = velocity;

    self->acceleration = params.acceleration;

    self->angle = params.angle;
    self->ang_velocity = params.ang_velocity;

    sphere3f_st * bound_sphere;
    bound_sphere = malloc(sizeof *bound_sphere);
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
    free(self->bound_sphere);
    free(self->velocity);
    free(self->position);
    free(self->axis);
    free(self);
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


point3f_st *
gameobj__unit_vector_facing(struct gameobj * self)
{
    //Returns the direction unit vector
    return NULL;
}


point3f_st *
gameobj__unit_vector_velocity(struct gameobj * self)
{
    //Returns the velocity unit vector
    return NULL;
}
