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

ship* ship_init_values(float px,
                       float py, 
                       float pz, 
                       float vx, 
                       float vy, 
                       float vz, 
                       float a)
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
    position->x = px;
    position->y = py;
    position->z = pz;
    self->position = position;

    velocity = malloc(sizeof *(velocity));
    memset(velocity, 0, sizeof *velocity);
    velocity->x = vx;
    velocity->y = vy;
    velocity->z = vz;
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
    ship* myship = ship_init_values(1, 2, 3, 1.1, 2.1, 3.1, 4.0);

    printf("Position x: %f, y: %f, z: %f\n", myship->position->x, myship->position->y, myship->position->z);
    printf("Velocity x: %f, y: %f, z: %f\n", myship->velocity->x, myship->velocity->y, myship->velocity->z);
    printf("Acceleration %f\n", myship->acceleration);

    ship_destroy(myship);

}
