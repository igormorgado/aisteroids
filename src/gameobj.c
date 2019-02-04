#include <stdbool.h>
#include <stdlib.h>

#include "gameobj.h"
#include "phys.h"


struct gameobj *
gameobj__init(void)
{
    struct gameobj * self;
    self = malloc(sizeof *self);

    self->size = 1.0;

    point3f * axis;
    axis = malloc(sizeof *axis);
    self->axis = axis;

    point3f * position;
    position = malloc(sizeof *position);
    self->position = position;

    point3f * velocity;
    velocity = malloc(sizeof *velocity);
    self->velocity = velocity;

    self->acceleration = 0.0;

    self->angle = 0.0;
    self->ang_velocity = 0.0;

    sphere3f * bound_sphere;
    bound_sphere = malloc(sizeof *bound_sphere);
    self->bound_sphere = bound_sphere;

    self->active = false;
    self->life_timer = 0;
    self->type = 0;
    self->obj_flags = OBJ_RESET;

    return self;
}


void 
gameobj__destroy(struct gameobj * self)
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


point3f *
gameobj__unit_vector_facing(struct gameobj * self)
{
    //Returns the direction unit vector
    return NULL;
}


point3f *
gameobj__unit_vector_velocity(struct gameobj * self)
{
    //Returns the velocity unit vector
    return NULL;
}
