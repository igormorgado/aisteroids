#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "ship.h"

enum CONTROLTYPE 
{
    CONTROLTYPE_NONE,
    CONTROLTYPE_HUMAN,
    CONTROLTYPE_AI
};

struct control_params 
{
    int type;
};

struct control 
{
    struct ship * ship;
    int type;
};

// Memory management
struct control * control__init(struct control_params params);
void *           control__free(struct control * self);

// Game 
void             control__update(struct control * self, float dt);
void             control__set_ship(struct control * self, struct ship * ship);
#endif /* __CONTROL_H__ */

