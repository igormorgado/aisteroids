#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef struct point3f point3f;
struct point3f {
    float x, y, z;
};

typedef struct ship ship;
struct ship {
    point3f* position;
    point3f* velocity;
    float acceleration;
};

ship* ship_init(void)
{
    ship *self;
    point3f *position, *velocity;

    self = malloc(sizeof *self);
    if (!self) {
        perror("ship malloc failed");
        return self;
    }
    memset(self, 0, sizeof *self);

    position = malloc(sizeof *(position));
    memset(position, 0, sizeof *position);
    self->position = position;

    velocity = malloc(sizeof *(velocity));
    memset(velocity, 0, sizeof *velocity);
    self->velocity = velocity;

    self->acceleration = 0;
    
    return self;
}

void ship_destroy(ship* self)
{
    free(self->position);
    self->position = NULL;

    free(self->velocity);
    self->velocity = NULL;

    free(self);
    self = NULL;
}

int main(void)
{
    ship* myship = ship_init();
    point3f p = { 1, 2, 3};
    printf("x: %f, y: %f, z: %f\n", p.x, p.y, p.z);

    myship->position->x  = 1.1;
    myship->position->y  = 2.1;
    myship->position->z  = 3.1;

    printf("x: %f, y: %f, z: %f\n", myship->position->x, myship->position->y, myship->position->z);

    ship_destroy(myship);

}
