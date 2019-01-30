#include <stdio.h>
#include <stdlib.h>

typedef struct point3f point3f;
struct point3f
{
    float x;
    float y;
    float z;
};

typedef struct sphere3f sphere3f;
struct sphere3f
{
    struct point3f;
    float r;
};

int main(void)
{
    point3f p = {.x = 1.1, .y = 2.1, .z = 3.1};
    sphere3f s = {.x = 1.2, .y = 2.2, .z = 3.2, .r = 1};

    printf("Point %.2f %.2f %.2f\n", p.x, p.y, p.z);
    printf("Ball  %.2f %.2f %.2f radius %.2f\n", s.x, s.y, s.z, s.r);

    return 0;
}
