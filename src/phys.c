#include <stdlib.h>
#include <math.h>

#include "phys.h"

double norm(const point3f *v) {
    return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

void unit_vector(const point3f * v, point3f * u)
{
    double n = norm(v);

    u->x = v->x / n;
    u->y = v->y / n;
    u->z = v->z / n;
}

void accelerate(point3f *velocity, const float acceleration, const float dt)
{
    velocity->x += dt * acceleration;
    velocity->y += dt * acceleration;
    velocity->z += dt * acceleration;
}

void move(point3f *position, const point3f *velocity, const float dt)
{
    position->x += dt * velocity->x;
    position->y += dt * velocity->y;
    position->z += dt * velocity->z;
}

void rotate(float *angle, const float angVelocity, const float dt)
{
    *angle += dt * angVelocity;
    *angle = fmod(*angle, 360);
}

