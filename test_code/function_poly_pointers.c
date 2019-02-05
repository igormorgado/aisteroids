#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* **************************************************
 * Euclidean geometry
 * **************************************************/
struct point { float x; float y; };

inline float distance(struct point p1, struct point p2);
       
float distance(struct point p1, struct point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}


/* **************************************************
 * POLYGON
 * **************************************************/

struct polygon
{
    int sides;
    struct point vertex[20];                // No more than 20 sided polygon
    float (*area)(struct polygon p);
    float (*perimeter)(struct polygon *p);
    void (*action)(void);
};

float perimeter(struct polygon *P);


struct polygon * polygon_init(int sides)
{
    struct polygon *poly;
    poly = malloc(sizeof *poly);
    poly->sides = sides;
    poly->perimeter = perimeter;
    return poly;
}

void polygon_destroy(struct polygon * poly)
{
    free(poly);
}

float polygon_perimeter(struct polygon *p)
{
    return p->perimeter(p);
}

/* Polygon Functions */
float perimeter(struct polygon * poly)
{
    float p = 0;
    for (int i = 0; i < poly->sides - 1; i++)
        p += distance(poly->vertex[i], poly->vertex[i+1]);
    return p + distance(poly->vertex[poly->sides - 1], poly->vertex[0]);
}


/* **************************************************
 * TRIANGLE
 * **************************************************/
struct triangle { 
    struct polygon; 
    float (*height)(void);
};

/* **************************************************
 * SQUARE
 * **************************************************/
struct square
{
    struct polygon;
    float (*height)(void);
};


/* **************************************************
 * MAIN CODE
 * **************************************************/
int main(void)
{
    // Method 1
    struct polygon p1;
    p1.sides = 3;
    p1.vertex[0] = (struct point){ .x = 0, .y = 0 };
    p1.vertex[1] = (struct point){ .5, 1 };
    p1.vertex[2].x = 1;
    p1.vertex[2].y = 0;
    p1.perimeter = &perimeter;
    printf("P1 %.2f\n", p1.perimeter(&p1));


    // Method 2
    struct polygon *p2 = polygon_init(3);
    struct point t[3] = { {0, 0}, {.5, 1}, {1, 0}};
    memcpy(p2->vertex, t, sizeof(t));
    printf("P2 %.2f\n", polygon_perimeter(p2));
    polygon_destroy(p2);

    return 0;
}

