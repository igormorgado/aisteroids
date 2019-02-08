#ifndef __HUMAN_CONTROL_H__
#define __HUMAN_CONTROL_H__

#include "control.h"

typedef struct human_control_params human_control_params_st;
struct human_control_params
{
    struct ship * ship;
    int type;
};

typedef struct human_control human_control_st;
struct human_control 
{
    struct control;
};

struct human_control * human_control__init(struct human_control_params params);
void                   human_control__free(struct human_control * self);
void                   human_control__update(struct human_control * self, float dt);
void                   human_control__set_ship(struct human_control * self, struct ship * ship);
#endif

