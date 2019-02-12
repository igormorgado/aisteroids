#ifndef __AI_CONTROL_H__
#define __AI_CONTROL_H__

#include "control.h"
#include "ship.h"

struct ai_control_params
{
    struct ship * ship;
    int type;
};

struct ai_control 
{
    struct control base;
};

struct ai_control * ai_control__init    (struct ai_control_params params);
void                ai_control__free    (struct ai_control * self);
void                ai_control__update  (struct ai_control * self, float dt);
void                ai_control__set_ship(struct ai_control * self, struct ship * ship);
#endif /* __AI_CONTROL_H__ */
