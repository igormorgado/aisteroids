#ifndef __GAMEOBJ_H__
#define __GAMEOBJ_H__

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

typedef struct gameobj gameobj;
struct gameobj {
    float size;

    point3f *axis;
    point3f *position;          /*x,y,z spatial position */
    point3f *velocity;          /*x,y,z velocity */
    float acceleration;         /* scalar acceleration */

    float angle;                /* Angle of direcion xy */
    float angVelocity;          /* Angle change velocity clockwise oriented */

    sphere3f *boundSphere;      /* Colision bounded sphere */

    bool active;                /* Is this object active ? */

    float lifeTimer;            /* Time before item being removed from world */

    int type;                   /* Object type */
    unsigned int objFlags;      /* Object flags */

    void (*draw)(void);         /* Pointer to the specialized object draw */
    void (*update)(void);       /* Pointer to the specialized object update */
    void (*iscolliding)(void);  /* Pointer to the function that check colision */
    void (*docollision)(void);  /* Pointer to the function that executes colision */
};

gameobj* gameobj__init(void);
void     gameobj__destroy(gameobj *self);
void     gameobj__update(gameobj *self, float dt);
point3f* gameobj__unit_vector_facing(gameobj* self);   //Returns the direction unit vector
point3f* gameobj__unit_vector_velocity(gameobj* self); //Returns the velocity unit vector

#endif
