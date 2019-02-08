#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct point point;
struct point
{
    float x;
    float y;
};

void rotate(float angle,  float srcx,  float srcy, float * dstx, float * dsty) 
{
   *dstx = srcx * cos(angle) - srcy * sin(angle);
   *dsty = srcx * sin(angle) + srcy * cos(angle);
}

typedef float triangle[3][2];

int main(void)
{
    triangle t = {
        {1,0},
        {0,1},
        {-1,0}
    };

    triangle d;

    for(int i=0; i<3; i++)
    {
        rotate( PI/4, t[i][0], t[i][1], &d[i][0], &d[i][1]);
    }

    for(int i=0; i<3; i++)
    {
        printf("%f %f\n", d[i][0], d[i][1]);
    }
}
