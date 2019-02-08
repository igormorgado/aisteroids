#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "phys.h"

double
norm(const point3f_st * v) {
    return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

void 
unit_vector(const point3f_st * v, point3f_st * u)
{
    double n = norm(v);

    u->x = v->x / n;
    u->y = v->y / n;
    u->z = v->z / n;
}

void 
accelerate(point3f_st * velocity, const float acceleration, const float dt)
{
    velocity->x += dt * acceleration;
    velocity->y += dt * acceleration;
    velocity->z += dt * acceleration;
}

void 
move(point3f_st * position, const point3f_st *velocity, const float dt)
{
    position->x += dt * velocity->x;
    position->y += dt * velocity->y;
    position->z += dt * velocity->z;
}

void 
rotate(float * angle, const float angVelocity, const float dt)
{
    *angle += dt * angVelocity;
    *angle = fmod(*angle, 360);
}

char *
point3f_fmt(const point3f_st * vector)
{
    char * s;
    const int nsize = 3;     // Number of elements in vector
    const int vsize = 5;     // Vector total size
    const int fsize = 2;     // Float precision size
    const int tsize = (nsize * (vsize + fsize + 1)) + (2 * (nsize - 1));

    s = malloc(tsize + 1);
    snprintf(s, tsize, "%*.*f, %*.*f, %*.*f", 
            vsize, fsize, vector->x,
            vsize, fsize, vector->y,
            vsize, fsize, vector->z);

    return s;
}
