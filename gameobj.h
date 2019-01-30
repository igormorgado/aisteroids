#ifndef __GAMEOBJ_H__
#define __GAMEOBJ_H__

enum
{
    NO_LIFE_TIMER = -1
}
enum
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

    point3f position;
    point3f axis;
    float angle;

    point3f velocity;
    float angVelocity;
    float acceleration;

    bool active;

    sphere3f boundSphere;

    int type;

    unsigned int objFlags;

    void (*draw)(void);
    void (*update)(void);
    void (*iscolliding)(void);
    void (*docollision)(void);
}

gameobj* gameobj__init(void);
void     gameobj__destroy(gameobj *self);
void     gameobj__update(gameobj *self, float dt);
point3f* gameobj__unit_vector_facing(gameobj* self);   //Returns the direction unit vector
point3f* gameobj__unit_vector_velocity(gameobj* self); //Returns the velocity unit vector

#endif
