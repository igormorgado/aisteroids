#include <stdlib.h>

#include "bullet.h"
#include "defs.h"
#include "common.h"

struct bullet *
bullet__init(struct gameobj * parent)
{
    struct bullet * self;
    self = smalloc(sizeof *self);
    self->base.obj_flags  = OBJ_RESET;
    self->base.obj_flags |= OBJ_BULLET;
    self->parent = parent;
    return self;
}

void
bullet__destroy(struct bullet * self)
{
    sfree(self);
}

void
bullet__do_collision(struct bullet * self, struct gameobj * obj)
{
    if(obj->active)
    {
        obj->explode();
        obj->do_collision((struct gameobj *)self);
    }
    self->base.active = false;

    // Is the owner a SHIP? if so ;-)
    if(self->parent->obj_flags &= OBJ_SHIP)
    {
        ship__increment_score((struct ship *) self->parent, ASTEROID_SCORE_VAL);
        ship__terminate_bullet((struct ship *) self->parent);
    }
}

