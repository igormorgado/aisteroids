#ifndef __GAMEOBJ_H__
#define __GAMEOBJ_H__

#include <stdbool.h>
#include "phys.h"

enum OBJFLAGS
{
   OBJ_RESET     = 0,
   OBJ_NONE      = 1 << 0,
   OBJ_ASTEROID  = 1 << 1,
   OBJ_SHIP      = 1 << 2,
   OBJ_BULLET    = 1 << 3,
   OBJ_EXPLOSION = 1 << 4,
   OBJ_POWERUP   = 1 << 5,
   OBJ_TARGET    = 1 << 6,
   OBJ_NOTIMER   = 1 << 7
};

typedef struct gameobj_params gameobj_params_st;
struct gameobj_params
{
    float size;
    float acceleration;          /* scalar acceleration */
    float angle;                 /* Angle of direcion xy */
    float ang_velocity;          /* Angle change velocity clockwise oriented */
    float active;
    float life_timer;
    float type;
};

typedef struct gameobj gameobj_st;
struct gameobj
{
    float size;

    point3f_st * axis;
    point3f_st * position;          /*x,y,z spatial position */
    point3f_st * velocity;          /*x,y,z velocity */
    float acceleration;          /* scalar acceleration */

    float angle;                 /* Angle of direcion xy */
    float ang_velocity;          /* Angle change velocity clockwise oriented */

    sphere3f_st * bound_sphere;     /* Colision bounded sphere */

    bool active;                 /* Is this object active ? */

    float life_timer;            /* Time before item being removed from world */

    int type;                    /* Object type */
    unsigned int obj_flags;      /* Object flags */

    void (*draw)(void);          /* Pointer to the specialized object draw */
    void (*update)(void);        /* Pointer to the specialized object update */
    void (*is_colliding)(void);  /* Pointer to the function that check colision */
    void (*do_collision)(struct gameobj * self);  /* Pointer to the function that executes colision */
    void (*explode)(void);       /* Pointer to the function that executes explosion */
};

// Memory management
struct gameobj * gameobj__init(struct gameobj_params params);
void             gameobj__free(struct gameobj * self);

void             gameobj__update(struct gameobj * self, float dt);
point3f_st *     gameobj__unit_vector_facing(struct gameobj * self);   //Returns the direction unit vector
point3f_st *     gameobj__unit_vector_velocity(struct gameobj * self); //Returns the velocity unit vector

#endif
