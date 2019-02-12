#include <stdlib.h>

#include "bullet.h"
#include "defs.h"

struct bullet *
bullet__init(struct bullet_params params)
{
    struct bullet * self;
    self = malloc(sizeof *self);

    self->base.size = params.size;

    struct point3f * axis;
    axis = malloc(sizeof *axis);
    self->base.axis = axis;

    struct point3f * position;
    position = malloc(sizeof *position);
    self->base.position = position;

    struct point3f * velocity;
    velocity = malloc(sizeof *velocity);
    self->base.velocity = velocity;

    self->base.acceleration = params.acceleration;

    self->base.angle = params.angle;
    self->base.ang_velocity = params.ang_velocity;

    struct sphere3f * bound_sphere;
    bound_sphere = malloc(sizeof *bound_sphere);
    self->base.bound_sphere = bound_sphere;

    self->base.active = params.active;
    self->base.life_timer = params.life_timer;
    self->base.type = params.type;
    self->base.obj_flags  = OBJ_RESET;
    self->base.obj_flags |= params.obj_flags;

    self->parent = params.parent;

    return self;
}

void
bullet__destroy(struct bullet * self)
{
    free(self->base.bound_sphere);
    free(self->base.velocity);
    free(self->base.position);
    free(self->base.axis);
    free(self);
}

void
bullet__do_collision(struct bullet * self, struct gameobj * obj)
{
    if(obj->active)
    {
        obj->explode();
        obj->do_collision((struct gameobj *)self);
    }
    self->base.active = false;

    // Is the owner a SHIP? if so ;-)
    if(self->parent->obj_flags &= OBJ_SHIP)
    {
        ship__increment_score((struct ship *) self->parent, ASTEROID_SCORE_VAL);
        ship__terminate_bullet((struct ship *) self->parent);
    }
}

