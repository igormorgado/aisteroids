#include <stdlib.h>

#include "ai_control.h"
#include "ship.h"

struct ai_control *
ai_control__init(struct ai_control_params params)
{
    struct ai_control * self;
    self = malloc(sizeof *self);
    self->base.ship = params.ship;
    self->base.type = params.type;

    return self;
}

void
ai_control__free(struct ai_control * self)
{
    free(self);
}

void
ai_control__update(struct ai_control *self, float dt)
{
    return;
}

void
ai_control__set_ship(struct ai_control * self, struct ship * ship)
{
    self->base.ship = ship;
}

