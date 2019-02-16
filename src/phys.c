#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "phys.h"
#include "common.h" 

double
norm(const struct point3f * v) {
    return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

void 
unit_vector(const struct point3f * v, struct point3f * u)
{
    double n = norm(v);

    u->x = v->x / n;
    u->y = v->y / n;
    u->z = v->z / n;
}

/*
 * This function changes its own first parameter
 * should we create a result parameter?
 */
void 
accelerate(struct point3f * velocity, const float acceleration, const float dt)
{
    velocity->x += dt * acceleration;
    velocity->y += dt * acceleration;
    velocity->z += dt * acceleration;
}

/*
 * This function changes its own first parameter
 * should we create a result parameter?
 */
void 
move(struct point3f * position, const struct point3f *velocity, const float dt)
{
    position->x += dt * velocity->x;
    position->y += dt * velocity->y;
    position->z += dt * velocity->z;
}

/*
 * This function changes its own first parameter
 * should we create a result parameter?
 */
void 
rotate(float * angle, const float angVelocity, const float dt)
{
    *angle += dt * angVelocity;
    *angle = fmod(*angle, 360);
}

char *
point3f_fmt(const struct point3f * vector)
{
    char * s;
    const int nsize = 3;     // Number of elements in vector
    const int vsize = 5;     // Vector total size
    const int fsize = 2;     // Float precision size
    const int tsize = (nsize * (vsize + 1)) + (2 * (nsize - 1));

    s = smalloc(tsize + 1);
    snprintf(s, tsize, "%*.*f, %*.*f, %*.*f", 
            vsize, fsize, vector->x,
            vsize, fsize, vector->y,
            vsize, fsize, vector->z);

    return s;
}
