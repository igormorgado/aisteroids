#include <stdbool.h>
#include <stdlib.h>

#include "gameobj.h"
#include "phys.h"


gameobj *
gameobj__init(void)
{
    gameobj * self;
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
    self->angVelocity = 0.0;

    sphere3f * boundSphere;
    boundSphere = malloc(sizeof *boundSphere);
    self->boundSphere = boundSphere;

    self->active = false;
    self->lifeTimer = 0;
    self->type = 0;
    self->objFlags = OBJ_RESET;

    return self;
}


void 
gameobj__destroy(gameobj * self)
{
    free(self->boundSphere);
    free(self->velocity);
    free(self->position);
    free(self->axis);
    free(self);
}


void
gameobj__update(gameobj * self, float dt)
{
    accelerate(self->velocity, self->acceleration, dt);
    move(self->position, self->velocity, dt);
    rotate(&(self->angle), self->angVelocity, dt);

    self->position->z = 0.0f;

    if((self->objFlags & OBJ_NOTIMER) == 0)
    {
        self->lifeTimer -= dt;
        if(self->lifeTimer < 0.0f) {
            self->active = false;
        }
    }
}


point3f *
gameobj__unit_vector_facing(gameobj * self)
{
    //Returns the direction unit vector
    return NULL;
}


point3f *
gameobj__unit_vector_velocity(gameobj * self)
{
    //Returns the velocity unit vector
    return NULL;
}
