#include <stdlib.h>

#include "control.h"
#include "ship.h"
#include "common.h" 

struct control *
control__init(struct control_params params)
{
    struct control * self;
    self = smalloc(sizeof *self);
    self->type = params.type;
    return self;
}

void *
control__free(struct control * self)
{
    return sfree(self);
}

void
control__update(struct control *self, float dt)
{
    //
}

void
control__set_ship(struct control * self, struct ship * ship)
{
    self->ship = ship;
}

