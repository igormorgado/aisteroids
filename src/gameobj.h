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

struct gameobj_params
{
	float size;
	float acceleration;		/* scalar acceleration */
	float angle;                 	/* Angle of direcion xy */
	float ang_velocity;          	/* Angle change velocity clockwise oriented */
	bool active;
	float life_timer;
	float type;
};

struct gameobj
{
	size_t usecnt;
	float size;

	struct point3f * axis;
	struct point3f * position;	/*x,y,z spatial position */
	struct point3f * velocity;   	/*x,y,z velocity */
	float acceleration;		/* scalar acceleration */

	float angle;			/* Angle of direcion xy */
	float ang_velocity;          	/* Angle change velocity clockwise oriented */

	struct sphere3f * bound_sphere; /* Colision bounded sphere */

	bool active;			/* Is this object active ? */

	float life_timer;            	/* Time before item being removed from world */

	int type;                    	/* Object type */
	unsigned int obj_flags;      	/* Object flags */

	void (*draw)(void);          	/* Pointer to the specialized object draw */
	void (*update)(void);        	/* Pointer to the specialized object update */
	void (*is_colliding)(void);  	/* Pointer to the function that check colision */
	void (*do_collision)(struct gameobj * self);  /* Pointer to the function that executes colision */
	void (*explode)(void);		/* Pointer to the function that executes explosion */
};

// Memory management
struct gameobj * gameobj__init(const struct gameobj_params params);
void             gameobj__free(struct gameobj * self);

void             gameobj__update(struct gameobj * self, float dt);
char *		 gameobj__fmt(const struct gameobj * self);
void		 gameobj__print(const struct gameobj * self);

void		 gameobj__unit_vector_facing(struct gameobj * self, struct point3f * unit);   //Returns the direction unit vector
void		 gameobj__unit_vector_velocity(struct gameobj * self, struct point3f * unit); //Returns the velocity unit vector

#endif /* __GAMEOBJ_H__ */
