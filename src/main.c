#include <stdio.h>

#include "main.h"

int main(void)
{
    struct ship* xip = ship__init();

    xip->position->x = 1.1;
    xip->position->y = 2.1;
    xip->position->z = 0.0;

    printf("My ship is at %.2f %.2f %.2f\n", xip->position->x, xip->position->y, xip->position->z);

    return 0;
}
