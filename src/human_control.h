#ifndef __HUMAN_CONTROL_H__
#define __HUMAN_CONTROL_H__

#include "control.h"

struct human_control 
{
    struct control;
    int placeholder;
};

struct human_control * human_control__init(struct ship * ship, int type);
void                   human_control__destroy(struct human_control * self);
void                   human_control__update(struct human_control * self, float dt);
void                   human_control__set_ship(struct human_control * self, struct ship * ship);
#endif

