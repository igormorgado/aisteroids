#include <stdlib.h>

#include "control.h"
#include "ship.h"

struct control * control__init(struct ship *ship, int type)
{
    struct control * self;
    self = malloc(sizeof *self);
    self->ship = ship;
    self->type = type;

    return self;

}

void control__destroy(struct control * self)
{
    free(self);
}

void control__update(struct control *self, float dt)
{

}

void control__set_ship(struct control * self, struct ship * ship)
{
    self->ship = ship;
}

