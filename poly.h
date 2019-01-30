#ifndef __POLY_H__
#define __POLY_H__

typedef struct point3f point3f;
struct point3f {
    float x;
    float y;
    float z;
};

typedef struct sphere3f sphere3f;
struct sphere3f {
    float x;
    float y;
    float z;
    float r;
};

double norm(point3f *v);
void unit_vector(const point3f * v, point3f * u);

#endif
