#ifndef __SHIP_H__
#define __SHIP_H__

#include <stdbool.h>

typedef struct ship ship;
struct ship {
    struct gameobj;
    Control* control;
    int activeBulletCount;
    bool thrust;
    bool revThrust;
    int shotPowerLevel;
    float invincibilityTimer;
};

// Memory management
ship*    ship__init(void);
void     ship__destroy(ship *self);

// Game loop
void     ship__update(ship *self, float dt);

// Controls
void     ship__thrust_on(ship *self);
void     ship__thrust_reverse(ship *self);
void     ship__thrust_off(ship *self);
void     ship__turn_left(ship *self);
void     ship__turn_right(ship *self);
void     ship__turn_stop(ship *self);
void     ship__stop(ship *self);
void     ship__hyperspace(ship *self);

// Power up
void     ship__get_powerup(int powerup);
int      ship__get_shot_level(void);
int      ship__get_num_bullets(void);
void     ship__inc_num_bullets(int num);
void     ship__make_invincible(float time);

// Bullet management
int      ship__max_bullet(void);
void     ship__terminate_bullet(void);
void     ship__shoot(void);
float    ship__get_closest_gun_angle(float angle);


point3f* ship__unit_vector_facing(gameobj* self);   //Returns the direction unit vector
point3f* ship__unit_vector_velocity(gameobj* self); //Returns the velocity unit vector

#endif
