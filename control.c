#include <stdlib.h>

#include "control.h"
#include "ship.h"

Control * control__init(Ship *ship, int type)
{
    Control* self;
    self = malloc(sizeof *self);
    self->ship = ship;
    self->type = type;

    return self;

}

void control__destroy(Control * self)
{
    free(self);
}

void control__update(Control *self, float dt)
{

}

void control__set_ship(Control * self, Ship * ship)
{
    self->ship = ship;
}

