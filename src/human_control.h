#ifndef __HUMAN_CONTROL_H__
#define __HUMAN_CONTROL_H__

#include "control.h"

struct human_control_params
{
    struct ship * ship;
    int type;
};

struct human_control 
{
    struct control base;
};

struct human_control * human_control__init(struct human_control_params params);
void *                 human_control__free(struct human_control * self);
void                   human_control__update(struct human_control * self, float dt);
void                   human_control__set_ship(struct human_control * self, struct ship * ship);
#endif /* __HUMAN_CONTROL_H__ */
