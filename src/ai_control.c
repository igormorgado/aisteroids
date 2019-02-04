#include <stdlib.h>

#include "ai_control.h"
#include "ship.h"

struct ai_control *
ai_control__init(struct ship *ship, int type)
{
    struct ai_control * self;
    self = malloc(sizeof *self);
    self->ship = ship;
    self->type = type;

    return self;

}

void
ai_control__destroy(struct ai_control * self)
{
    free(self);
}

void
ai_control__update(struct ai_control *self, float dt)
{

}

void
ai_control__set_ship(struct ai_control * self, struct ship * ship)
{
    self->ship = ship;
}

