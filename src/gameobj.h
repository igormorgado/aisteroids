#ifndef __GAMEOBJ_H__
#define __GAMEOBJ_H__

#include <stdbool.h>
#include "phys.h"

enum OBJFLAGS
{
   OBJ_RESET    = 0,
   OBJ_NONE     = 1 << 0,
   OBJ_ASTEROID = 1 << 1,
   OBJ_SHIP     = 1 << 2,
   OBJ_BULLET   = 1 << 3,
   OBJ_EXP      = 1 << 4,
   OBJ_POWERUP  = 1 << 5,
   OBJ_TARGET   = 1 << 6,
   OBJ_NOTIMER  = 1 << 7
};

struct gameobj {
    float size;

    point3f * axis;
    point3f * position;          /*x,y,z spatial position */
    point3f * velocity;          /*x,y,z velocity */
    float acceleration;         /* scalar acceleration */

    float angle;                /* Angle of direcion xy */
    float ang_velocity;          /* Angle change velocity clockwise oriented */

    sphere3f * bound_sphere;      /* Colision bounded sphere */

    bool active;                /* Is this object active ? */

    float life_timer;            /* Time before item being removed from world */

    int type;                   /* Object type */
    unsigned int obj_flags;      /* Object flags */

    void (*draw)(void);         /* Pointer to the specialized object draw */
    void (*update)(void);       /* Pointer to the specialized object update */
    void (*is_colliding)(void);  /* Pointer to the function that check colision */
    void (*do_collision)(struct gameobj * self);  /* Pointer to the function that executes colision */
    void (*explode)(void);      /* Pointer to the function that executes explosion */
};

struct gameobj * gameobj__init(void);
void             gameobj__destroy(struct gameobj * self);
void             gameobj__update(struct gameobj * self, float dt);
point3f *        gameobj__unit_vector_facing(struct gameobj * self);   //Returns the direction unit vector
point3f *        gameobj__unit_vector_velocity(struct gameobj * self); //Returns the velocity unit vector

#endif
