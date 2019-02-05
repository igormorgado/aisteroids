#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point { float x; float y; };

struct poligon
{
    int sides;
    struct point vertex[20];                // No more than 20 sided polygon
    float (*area)(struct poligon p);
    float (*perimeter)(struct poligon p);
    void (*action)(void);
};


struct triangle { struct poligon; float (*height)(void);
};


struct square
{
    struct poligon;
    float (*height)(void);
};


inline float distance(struct point p1, struct point p2);
       
float distance(struct point p1, struct point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float perimeter(struct poligon P)
{
    int i;
    float p = 0;

    for (i = 0; i < P.sides - 1; i++)
    {    
        p += distance(P.vertex[i], P.vertex[i+1]);
    }
    p += distance(P.vertex[i], P.vertex[0]);

    return p;
}

int main(void)
{
    struct poligon p1;
    
    p1.sides = 3;
    //
    // Three different ways to assign values to a struct
    p1.vertex[0] = (struct point){ .x = 0, .y = 0 };
    p1.vertex[1] = (struct point){ .5, 1 };
    p1.vertex[2].x = 1;
    p1.vertex[2].y = 0;

    p1.perimeter = &perimeter;

    printf("P1 %.2f\n", p1.perimeter(p1));


    struct poligon *p2;
    p2 = malloc(sizeof *p2);
    p2->sides = 3;
    // Is there any way to assign all three vertex at same time?
    p2->vertex = (struct point) { (struct point){ 0, 0 },
                                  (struct point){.5, 1 },
                                  (struct point){ 1, 0 }
    };
    p2->perimeter = &perimeter;
    printf("P2 %.2f\n", p2->perimeter(*p2));

    return 0;
}

