#include <stdlib.h>

#include "bullet.h"

struct bullet *
bullet__init(void)
{
    struct bullet * self;
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
    self->obj_flags  = OBJ_RESET;
    self->obj_flags |= OBJ_BULLET;

    return self;
}

void
bullet__destroy(struct bullet * self)
{
    free(self->bound_sphere);
    free(self->velocity);
    free(self->position);
    free(self->axis);
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
    self->active = false;

    if(self->player_bullet)
    {
        // HOW TO ACCESS GAME STATE FROM HERE TO ADD A SCORE?
        // Any other ideas to increment score? maybe from ship?
        // game__increment_score(game, ASTEROID_SCORE_VAL);
        // ship__terminate_bullet(
    }
}

