#include <stdlib.h>

#include "human_control.h"
#include "ship.h"
#include "common.h"

struct human_control *
human_control__init(struct human_control_params params)
{
    struct human_control * self;
    self = smalloc(sizeof *self);
    self->base.ship = params.ship;
    self->base.type = params.type;

    return self;

}

void *
human_control__free(struct human_control * self)
{
    return sfree(self);
}

// void
// human_control__update(struct human_control *self, float dt)
// {
// 
// }

void
human_control__set_ship(struct human_control * self, struct ship * ship)
{
    self->base.ship = ship;
}

