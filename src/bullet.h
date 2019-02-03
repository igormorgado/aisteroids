#ifndef __BULLET_H__
#define __BULLET_H__

#include <stdbool.h>
#include "gameobj.h"
#include "control.h"

struct bullet {
    struct gameobj;
}

// Memory management
struct bullet *     bullet__init(void);
void                bullet__destroy(struct bullet * self);

// Game loop
void                bullet__update(struct bullet * self);


// Physics
void                bullet__do_collision(struct bullet * self, struct gameobj * obj);


// Formatting
char *              bullet__fmt(const struct bullet * self);

#endif
