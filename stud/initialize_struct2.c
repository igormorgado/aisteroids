#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

enum
{
   OBJ_NONE     = 1 << 0,
   OBJ_ASTEROID = 1 << 1,
   OBJ_SHIP     = 1 << 2,
   OBJ_BULLET   = 1 << 3,
   OBJ_EXP      = 1 << 4,
   OBJ_POWERUP  = 1 << 5,
   OBJ_TARGET   = 1 << 6,
   OBJ_RESERVED = 1 << 7
};

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

ship* ship_init_struct(point3f* p, point3f *v, float a)
{
    ship *self;
    point3f *position, *velocity;

    self = malloc(sizeof *self);
    if (!self) {
        perror("ship malloc failed");
        return self;
    }
    memset(self, 0, sizeof *self);

    position = malloc(sizeof *position);
    memcpy(position, p, sizeof *position);
    self->position = position;

    velocity = malloc(sizeof *velocity);
    memcpy(velocity, v, sizeof *velocity);
    self->velocity = velocity;

    self->acceleration = a;

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
    point3f p = {1, 2, 3};
    point3f v = {1.1, 2.1, 3.1};
    float a = 4.0;

    ship* myship = ship_init_struct(&p, &v, a);

    printf("Position x: %f, y: %f, z: %f\n", myship->position->x, myship->position->y, myship->position->z);
    printf("Velocity x: %f, y: %f, z: %f\n", myship->velocity->x, myship->velocity->y, myship->velocity->z);
    printf("Acceleration %f\n", myship->acceleration);

    ship_destroy(myship);

}
