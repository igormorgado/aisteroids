#include <stdlib.h>
#include <math.h>

#include "poly.h"

double norm(point3f *v) {
    return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

void unit_vector(const point3f * v, point3f * u)
{
    double n = norm(v);

    u->x = v->x / n;
    u->y = v->y / n;
    u->z = v->z / n;
}
