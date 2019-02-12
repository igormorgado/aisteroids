#include <stdbool.h>
#include <stdlib.h>

#include "ship.h"
#include "phys.h"
#include "debug.h"

struct ship *
ship__init(struct ship_params params)
{
    struct ship * self;
    self = malloc(sizeof *self);

    self->base.size = params.base.size;

    struct point3f * axis;
    axis = malloc(sizeof *axis);
    self->base.axis = axis;

    struct point3f * position;
    position = malloc(sizeof *position);
    self->base.position = position;

    struct point3f * velocity;
    velocity = malloc(sizeof *velocity);
    self->base.velocity = velocity;

    self->base.acceleration = params.base.acceleration;

    self->base.angle = params.base.angle;
    self->base.ang_velocity = params.base.ang_velocity;

    struct sphere3f * bound_sphere;
    bound_sphere = malloc(sizeof *bound_sphere);
    self->base.bound_sphere = bound_sphere;

    self->base.active = params.base.active;
    self->base.life_timer = params.base.life_timer;
    self->base.type = params.base.type;
    self->base.obj_flags  = OBJ_RESET;        // Reset flags
    self->base.obj_flags |= OBJ_SHIP;      // Controlled ship has no timer

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
    free(self->base.bound_sphere);
    free(self->base.velocity);
    free(self->base.axis);
    free(self->base.position);
    free(self->control);  
    free(self);
}

void
ship__update(struct ship * self, float dt)
{
	char *s1 = ship__fmt(self);
	debug_print("%s\n", s1 );
	free(s1);

	accelerate(self->base.velocity, self->base.acceleration, dt);
	char *s2 = ship__fmt(self);
	debug_print("%s\n", s2);
	free(s2);

	move(self->base.position, self->base.velocity, dt);

	char *s3 = ship__fmt(self);
	debug_print("%s\n", s3);
	free(s3);

	rotate(&(self->base.angle), self->base.ang_velocity, dt);

	char *s4 = ship__fmt(self);
	debug_print("%s\n", s4);
	free(s4);

	self->base.position->z = 0.0f;

	char *s5 = ship__fmt(self);
	debug_print("%s\n", s5);
	free(s5);

	if((self->base.obj_flags & OBJ_NOTIMER) == 0) {
		self->base.life_timer -= dt;
		if(self->base.life_timer < 0.0f) {
			self->base.active = false;
		}
	}
}

void
ship__increment_score(struct ship * self, int value) 
{
    self->score += value;
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
    self->base.ang_velocity = 0.0;
}

void 
ship__stop(struct ship * self)
{
    self->base.velocity->x = 0.;
    self->base.velocity->y = 0.;
    self->base.velocity->z = 0.;
    self->base.acceleration = 0.;
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

    char *pp = point3f_fmt(self->base.position);	
    char *pv = point3f_fmt(self->base.velocity);

    snprintf(s, tsize, "P(%s), V(%s), A(%.2f), O(%.2f), T(%.2f)",
            pp,
            pv,
            self->base.acceleration, self->base.angle, self->base.ang_velocity);

    free(pv);
    free(pp);
    return s;
}
