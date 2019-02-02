#include <stdbool.h>
#include <stdlib.h>

#include "ship.h"

struct ship * ship__init(void)
{
    // Is there any way to use gameobj__init() then just initialize
    // what is left ?
    struct ship * self;
    self = malloc(sizeof *self);

    self->size = 1.0;

    point3f* axis;
    axis = malloc(sizeof *axis);
    self->axis = axis;

    point3f* position;
    position = malloc(sizeof *position);
    self->position = position;

    point3f* velocity;
    velocity = malloc(sizeof *velocity);
    self->velocity = velocity;

    self->acceleration = 0.0;

    self->angle = 0.0;
    self->angVelocity = 0.0;

    sphere3f* boundSphere;
    boundSphere = malloc(sizeof *boundSphere);
    self->boundSphere = boundSphere;

    self->active = false;
    self->lifeTimer = 0;
    self->type = 0;
    self->objFlags  = OBJ_RESET;        // Reset flags
    self->objFlags |= OBJ_NOTIMER;      // Controlled ship has no timer

    // struct ship only members
    struct control * control;
    control = malloc(sizeof *control);
    self->control = control;

    self->activeBulletCount = 0;
    self->thrust = false;
    self->revThrust = false;
    self->shotPowerLevel = 0;
    self->invincibilityTimer = 0;
   
    return self;
}


void ship__destroy(struct ship * self)
{
    free(self->control);
    free(self->boundSphere);
    free(self->velocity);
    free(self->axis);
    free(self->position);
    free(self->control);
    free(self);
}

void ship__update(struct ship * self, float dt)
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


void ship__thrust_on(struct ship * self)
{
    self->thrust = true;
    self->revThrust = false;
}

void ship__thrust_reverse(struct ship * self)
{
    self->thrust = false;
    self->revThrust = true;
}

void ship__thrust_off(struct ship * self)
{
    self->thrust = false;
    self->revThrust = false;
}

void ship__turn_left(struct ship * self)
{
    ;
}

void ship__turn_right(struct ship * self)
{
    ;
}

void ship__turn_stop(struct ship * self)
{
    self->angVelocity = 0.0;
}

void ship__stop(struct ship * self)
{
    ;
}

void ship__hyperspace(struct ship * self)
{
    ;
}

void ship__get_powerup(struct ship * self, int powerup)
{
    ;
}

int ship__get_shot_level(struct ship * self) {
    return self->shotPowerLevel;
}

int ship__get_num_bullets(struct ship * self) {
    return self->activeBulletCount;
}

void ship__inc_num_bullets(struct ship * self, int num)
{
    self->activeBulletCount += num;
}

void ship__make_incincible(struct ship * self, float time)
{
    self->invincibilityTimer += time;
}

int ship__max_bullet(struct ship * self)
{
    ;
}

void ship__terminate_bullet(struct ship * self)
{
    if(self->activeBulletCount > 0)
        self->activeBulletCount--;
}

void ship__shoot(struct ship * self)
{
    ;
}

float ship__get_closest_gun_angle(struct ship * self, float angle)
{
    ;
}

