#ifndef __PHYS_H__
#define __PHYS_H__

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

double norm(const point3f * v);
void unit_vector(const point3f * v, point3f * u);

void accelerate(point3f * velocity, const float acceleration, const float dt);
void move(point3f * position, const point3f * velocity, const float dt);
void rotate(float * angle, const float angVelocity, const float dt);

char * point3f_fmt(const point3f * vector);

#endif
