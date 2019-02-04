#ifndef __AI_CONTROL_H__
#define __AI_CONTROL_H__

#include "control.h"

struct ai_control 
{
    struct control;
    int placeholder;
};

struct ai_control * ai_control__init    (struct ship * ship, int type);
void                ai_control__destroy (struct ai_control * self);
void                ai_control__update  (struct ai_control * self, float dt);
void                ai_control__set_ship(struct ai_control * self, struct ship * ship);
#endif

