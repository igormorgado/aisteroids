#ifndef __SHIP_H__
#define __SHIP_H__

#include <stdbool.h>
#include "gameobj.h"
#include "control.h"

struct ship {
    struct gameobj;

    struct control * control;
    int activeBulletCount;
    bool thrust;
    bool revThrust;
    int shotPowerLevel;
    float invincibilityTimer;
};

// Memory management
struct ship *   ship__init(void);
void            ship__destroy(struct ship * self);

// Game loop
void            ship__update(struct ship * self, float dt);

// Controls
void            ship__thrust_on(struct ship * self);
void            ship__thrust_reverse(struct ship * self);
void            ship__thrust_off(struct ship * self);
void            ship__turn_left(struct ship * self);
void            ship__turn_right(struct ship * self);
void            ship__turn_stop(struct ship * self);
void            ship__stop(struct ship * self);
void            ship__hyperspace(struct ship * self);

// Power up
void            ship__get_powerup(struct ship * self, int powerup);
int             ship__get_shot_level(struct ship * self);
int             ship__get_num_bullets(struct ship * self);
void            ship__inc_num_bullets(struct ship * self, int num);
void            ship__make_invincible(struct ship * self, float time);

// Bullet management
int             ship__max_bullet(struct ship * self);
void            ship__terminate_bullet(struct ship * self);
void            ship__shoot(struct ship * self);
float           ship__get_closest_gun_angle(struct ship * self, float angle);


// Formatting functions
char *          ship__fmt(const struct ship * self);
#endif
