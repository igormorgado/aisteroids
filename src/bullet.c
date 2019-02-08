#include <stdlib.h>

#include "bullet.h"

struct bullet *
bullet__init(struct bullet_params params)
{
    struct bullet * self;
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
    self->obj_flags  = OBJ_RESET;
    self->obj_flags |= params.obj_flags;

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

