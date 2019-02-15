#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


typedef struct point3f point3f;
struct point3f {
    float x;
    float y;
    float z;
};

double norm(point3f *v);
point3f* unit_vector(point3f *v);

double norm(point3f *v) {
    return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

point3f* unit_vector(point3f *v) {

    double n;
    point3f *u;
    u = malloc(sizeof *u);

    n = norm(v);

    u->x = v->x / n;
    u->y = v->y / n;
    u->z = v->z / n;

    return u;
}

int main(void) {
    point3f v = {1, 2, 3};
    point3f *u = unit_vector(&v);

    printf("v: %2f %2f %2f\n", v.x, v.y, v.z);
    printf("v norm: %2f\n", norm(&v));

    printf("u: %2f %2f %2f\n", u->x, u->y, u->z);
    printf("u norm: %2f\n", norm(u));

    free(u);

    return 0;
}
