#ifndef __SHIP_H__
#define __SHIP_H__

#include <stdbool.h>
#include "gameobj.h"
#include "control.h"

typedef struct ship Ship;
struct ship {
    struct gameobj;

    Control * control;
    int activeBulletCount;
    bool thrust;
    bool revThrust;
    int shotPowerLevel;
    float invincibilityTimer;
};

// Memory management
Ship *   ship__init(void);
void     ship__destroy(Ship * self);

// Game loop
void     ship__update(Ship * self, float dt);

// Controls
void     ship__thrust_on(Ship * self);
void     ship__thrust_reverse(Ship * self);
void     ship__thrust_off(Ship * self);
void     ship__turn_left(Ship * self);
void     ship__turn_right(Ship * self);
void     ship__turn_stop(Ship * self);
void     ship__stop(Ship * self);
void     ship__hyperspace(Ship * self);

// Power up
void     ship__get_powerup(Ship * self, int powerup);
int      ship__get_shot_level(Ship * self);
int      ship__get_num_bullets(Ship * self);
void     ship__inc_num_bullets(Ship * self, int num);
void     ship__make_invincible(Ship * self, float time);

// Bullet management
int      ship__max_bullet(Ship * self);
void     ship__terminate_bullet(Ship * self);
void     ship__shoot(Ship * self);
float    ship__get_closest_gun_angle(Ship * self, float angle);

#endif
