#ifndef __PHYS_H__
#define __PHYS_H__

struct point3f {
    float x;
    float y;
    float z;
};


struct sphere3f {
    float x;
    float y;
    float z;
    float r;
};

struct point3f * point3f_init(struct point3f params);
void *        point3f_free(struct point3f * self);

struct sphere3f * sphere3f_init(struct sphere3f params);
void *         sphere3f_free(struct sphere3f *self);

double norm(const struct point3f * v);
void unit_vector(const struct point3f * v, struct point3f * u);

void accelerate(struct point3f * velocity, const float acceleration, const float dt);
void move(struct point3f * position, const struct point3f * velocity, const float dt);
void rotate(float * angle, const float angVelocity, const float dt);

char * point3f_fmt(const struct point3f * vector);

#endif /* __PHYS_H__ */
