#include <stdlib.h>

#include "control.h"
#include "ship.h"

struct control *
control__init(struct control_params params)
{
    struct control * self;
    self = malloc(sizeof *self);
    self->type = params.type;
    return self;
}

void
control__free(struct control * self)
{
    free(self);
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

