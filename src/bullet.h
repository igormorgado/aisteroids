#ifndef __BULLET_H__
#define __BULLET_H__

#include <stdbool.h>
#include "gameobj.h"
#include "control.h"

typedef struct bullet_params bullet_params_st;
struct bullet_params {
    float size;
    float acceleration;
    float angle;
    float ang_velocity;
    bool active;
    float life_timer;
    int type;
    unsigned int obj_flags;
};

typedef struct bullet bullet_st;
struct bullet {
    struct gameobj;
    bool player_bullet;
};

// Memory management
struct bullet *     bullet__init(struct bullet_params params);
void                bullet__free(struct bullet * self);

// Game loop
void                bullet__update(struct bullet * self);


// Physics
void                bullet__do_collision(struct bullet * self, struct gameobj * obj);


// Formatting
char *              bullet__fmt(const struct bullet * self);

#endif
