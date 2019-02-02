#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "ship.h"

enum CONTROLTYPE 
{
    CONTROLTYPE_NONE,
    CONTROLTYPE_HUMAN,
    CONTROLTYPE_AI
};

typedef struct control Control;
struct control 
{
    Ship * ship;
    int type;
};

Control * control__init(Ship * ship, int type);
void control__destroy(Control * self);
void control__update(Control * self, float dt);
void control__set_ship(Control * self, Ship * ship);
#endif

