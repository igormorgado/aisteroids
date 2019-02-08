#include <stdbool.h>
#include <stdlib.h>

#include "ship.h"
#include "phys.h"
#include "debug.h"

struct ship *
ship__init(ship_params_st params)
{
    struct ship * self;
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

    self->active = false;
    self->life_timer = params.life_timer;
    self->type = params.type;
    self->obj_flags  = OBJ_RESET;        // Reset flags
    self->obj_flags |= OBJ_SHIP;      // Controlled ship has no timer

    // struct ship only members
    struct control * control;
    control = malloc(sizeof *control);
    self->control = control;

    self->active_bullet_count = params.active_bullet_count;
    self->thrust = false;
    self->rev_thrust = false;
    self->shot_power_level = 0;
    self->invincibility_timer = params.invincibility_timer;
   
    return self;
}


void
ship__free(struct ship * self)
{
    free(self->bound_sphere);
    free(self->velocity);
    free(self->axis);
    free(self->position);
    free(self->control);  
    free(self);
}

void
ship__update(struct ship * self, float dt)
{
    debug_print("%s\n", ship__fmt(self));
    accelerate(self->velocity, self->acceleration, dt);
    debug_print("%s\n", ship__fmt(self));
    move(self->position, self->velocity, dt);
    debug_print("%s\n", ship__fmt(self));
    rotate(&(self->angle), self->ang_velocity, dt);
    debug_print("%s\n", ship__fmt(self));
    self->position->z = 0.0f;
    debug_print("%s\n", ship__fmt(self));

    if((self->obj_flags & OBJ_NOTIMER) == 0)
    {
        self->life_timer -= dt;
        if(self->life_timer < 0.0f) {
            self->active = false;
        }
    }
}


void
ship__thrust_on(struct ship * self)
{
    self->thrust = true;
    self->rev_thrust = false;
}

void
ship__thrust_reverse(struct ship * self)
{
    self->thrust = false;
    self->rev_thrust = true;
}

void
ship__thrust_off(struct ship * self)
{
    self->thrust = false;
    self->rev_thrust = false;
}

void
ship__turn_left(struct ship * self)
{
    ;
}

void
ship__turn_right(struct ship * self)
{
    ;
}

void 
ship__turn_stop(struct ship * self)
{
    self->ang_velocity = 0.0;
}

void 
ship__stop(struct ship * self)
{
    self->velocity->x = 0.;
    self->velocity->y = 0.;
    self->velocity->z = 0.;
    self->acceleration = 0.;
}

void 
ship__hyperspace(struct ship * self)
{
    ;
}

void 
ship__get_powerup(struct ship * self, int powerup)
{
    ;
}

int 
ship__get_shot_level(struct ship * self) {
    return self->shot_power_level;
}

int 
ship__get_num_bullets(struct ship * self) {
    return self->active_bullet_count;
}

void 
ship__inc_num_bullets(struct ship * self, int num)
{
    self->active_bullet_count += num;
}

void 
ship__make_incincible(struct ship * self, float time)
{
    self->invincibility_timer += time;
}

int 
ship__max_bullet(struct ship * self)
{
    return 0;
}

void 
ship__terminate_bullet(struct ship * self)
{
    if(self->active_bullet_count > 0)
        self->active_bullet_count--;
}

void 
ship__shoot(struct ship * self)
{
    ;
}

float 
ship__get_closest_gun_angle(struct ship * self, float angle)
{
    return 0;
}

char *
ship__fmt(const struct ship * self)
{
    const size_t tsize = 100;
    char * s;
    s = malloc(tsize + 1);

    snprintf(s, tsize, "P(%s), V(%s), A(%.2f), O(%.2f), T(%.2f)",
            point3f_fmt(self->position),
            point3f_fmt(self->velocity),
            self->acceleration, self->angle, self->ang_velocity);

    return s;
}
