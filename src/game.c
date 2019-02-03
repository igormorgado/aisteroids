#include "game.h"
#include "phys.h"

void
game__increment_score(struct game * self, int value) 
{
    self->score += value;
}
