#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ship.h"
#include "phys.h"
#include "debug.h"
#include "common.h"

struct ship *
ship__init(void)
{
    struct ship * self;
    self = smalloc(sizeof *self);
    self->base.obj_flags  = OBJ_RESET;        // Reset flags
    self->base.obj_flags |= OBJ_SHIP;      // Controlled ship has no timer

    // struct ship only members
    struct control * control;
    control = smalloc(sizeof *control);
    self->control = control;

    self->score = 0;
    self->thrust = false;
    self->rev_thrust = false;
    self->shot_power_level = 0;
    self->invincibility_timer = 0;
   
    return self;
}

void *
ship__free(struct ship * self)
{
    sfree(self->control);  
    return sfree(self);
}

void
ship__update(struct ship * self, float dt)
{
	debug_print_ship_fmt(self);
	accelerate(&self->base.velocity, self->base.acceleration, dt);
	debug_print_ship_fmt(self);
	move(&self->base.position, &self->base.velocity, dt);
	debug_print_ship_fmt(self);
	rotate(&(self->base.angle), self->base.ang_velocity, dt);
	debug_print_ship_fmt(self);
	self->base.position.z = 0.0f;
	debug_print_ship_fmt(self);
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
    self->base.velocity.x = 0.;
    self->base.velocity.y = 0.;
    self->base.velocity.z = 0.;
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
    s = smalloc(tsize + 1);

    char *pp = point3f_fmt(&self->base.position);	
    char *pv = point3f_fmt(&self->base.velocity);

    snprintf(s, tsize, "P(%s), V(%s), A(%.2f), O(%.2f), T(%.2f)",
            pp,
            pv,
            self->base.acceleration, self->base.angle, self->base.ang_velocity);

    sfree(pv);
    sfree(pp);
    return s;
}
