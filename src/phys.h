#ifndef __PHYS_H__
#define __PHYS_H__

typedef struct point3f point3f_params_st;
typedef struct point3f point3f_st;
struct point3f {
    float x;
    float y;
    float z;
};


typedef struct sphere3f sphere3f_params_st;
typedef struct sphere3f sphere3f_st;
struct sphere3f {
    float x;
    float y;
    float z;
    float r;
};

point3f_st * point3d_init(point3f_params_st params);
void         point3d_free(point3f_st * self);

sphere3f_st * sphere3f_init(sphere3f_params_st params);
void          sphere3f_free(sphere3f_st *self);

double norm(const point3f_st * v);
void unit_vector(const point3f_st * v, point3f_st * u);

void accelerate(point3f_st * velocity, const float acceleration, const float dt);
void move(point3f_st * position, const point3f_st * velocity, const float dt);
void rotate(float * angle, const float angVelocity, const float dt);

char * point3f_fmt(const point3f_st * vector);

#endif
