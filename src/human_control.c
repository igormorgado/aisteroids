#include <stdlib.h>

#include "human_control.h"
#include "ship.h"

struct human_control *
human_control__init(struct ship *ship, int type)
{
    struct human_control * self;
    self = malloc(sizeof *self);
    self->ship = ship;
    self->type = type;

    return self;

}

void
human_control__destroy(struct human_control * self)
{
    free(self);
}

void
human_control__update(struct human_control *self, float dt)
{

}

void
human_control__set_ship(struct human_control * self, struct ship * ship)
{
    self->ship = ship;
}

