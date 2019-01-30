#include <stdbool.h>

#include "gameobj.h"
#include "poly.h"


gameobj* gameobj__init(void)
{
    gameobj* self;
    point3f* position, axis, velocity;
    sphere3f* boundSphere;
    
    
    self = malloc(sizeof *self);
    position = malloc(sizeof *position);
    axis = malloc(sizeof *axis);
    velocity = malloc(sizeof *velocity);
    boundSphere = malloc(sizeof *boundSphere);

    self->size = 1.0;
    self->position = position;
    self->axis = axis;
    self->velocity = velocity;
    self->boundSphere = boundSpehere;

    self->angle = 0.0;
    self->angVelocity = 0.0;
    self->acceleration = 0.0;
    self->active = false;
    self->type = 0;
    self->objFlags = OBJ_RESET;
}


void gameobj__destroy(gameobj *self)
{
    free(self->boundSpehere);
    free(self->velocity);
    free(self->axis);
    free(self->position);
    free(self);
}


void gameobj__update(gameobj* self, float dt)
{
    self->velocity +=  dt * self->acceleration;
    self->position +=  dt * self->velocity;
    self->angle    += (dt * self->angVelocity) % 360;

    self->position->z = 0.0f;

    if((self->objFlags & OBJ_NOTIMER) == 0)
    {
        self->lifeTimer -= dt;
        if(self->lifeTimer < 0.0f) {
            self->active = false;
        }
    }
}


point3f* gameobj__unit_vector_facing(gameobj* self)
{
    //Returns the direction unit vector
    return NULL;
}


point3f* gameobj__unit_vector_velocity(gameobj* self)
{
    //Returns the velocity unit vector
    return NULL;
}
