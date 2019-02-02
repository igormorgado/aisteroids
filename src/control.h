#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "ship.h"

enum CONTROLTYPE 
{
    CONTROLTYPE_NONE,
    CONTROLTYPE_HUMAN,
    CONTROLTYPE_AI
};

struct control 
{
    struct ship * ship;
    int type;
};

struct control * control__init(struct ship * ship, int type);
void control__destroy(struct control * self);
void control__update(struct control * self, float dt);
void control__set_ship(struct control * self, struct ship * ship);
#endif

