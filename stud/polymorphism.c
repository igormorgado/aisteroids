#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

/* **************************************************
 * The basics
 * **************************************************/
struct point { float x; float y; };

inline float distance(struct point p1, struct point p2);
       
// a.k.a. l2 norm
float distance(struct point p1, struct point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}


/* **************************************************
 * POLYGON
 * **************************************************/

/* Header */

struct polygon
{
    int sides;                              // All polygons have sides
    struct point vertex[20];                // No more than 20 sided polygon
    void  (*destroy)();                     // Unknown parameters
    float (*area)();                        // Unknown parameters
    float (*perimeter)();                   // Unknown parameters
    void  (*action)();                      // A polygon also needs some action
};

float null_area();
float null_perimeter();
void  null_action();

float generic_area(struct polygon * p);
float generic_perimeter(struct polygon * p);
void  generic_action(void);

struct polygon * polygon_init(int sides);
void             polygon_destroy(struct polygon * p);
float            polygon_area(struct polygon *poly);
float            polygon_perimeter(struct polygon * p);
void             polygon_action(struct polygon * p);

bool            all_sides_are_congruent(struct polygon *p);

/* NULL function */

float null_area()
{
    return -1;
}

float null_perimeter()
{
    return -1;
}

void null_action()
{
    return;
}

float generic_area(struct polygon * poly)
{
    return null_area();                   //  Not implemented
}

float generic_perimeter(struct polygon * poly)
{
    float p = 0;
    for (int i = 0; i < poly->sides - 1; i++)
        p += distance(poly->vertex[i], poly->vertex[i+1]);
    return p + distance(poly->vertex[poly->sides - 1], poly->vertex[0]);
}

void generic_action(void)
{
    printf("I'm idle!\n");                  // Lazy Polygon - not much action
}

/* Specialized functions */

struct polygon * polygon_init(int sides)
{
    struct polygon *poly;
    poly = malloc(sizeof *poly);
    poly->sides = sides;
    poly->perimeter = generic_perimeter;
    poly->area = generic_area;
    poly->action = generic_action;
    poly->destroy = free;       // Like a generic destroy ;-)
    return poly;
}

void polygon_destroy(struct polygon * poly)
{
    poly->destroy(poly);
}

float polygon_perimeter(struct polygon *poly)
{
    return poly->perimeter(poly);
}

float polygon_area(struct polygon *poly)
{
    return poly->area(poly);
}

void polygon_action(struct polygon *poly)
{
    printf("Poly addr %p: ",(void *)poly);
    poly->action();
}

bool all_sides_are_congruent(struct polygon *p)
{
    float t;
    float s = distance(p->vertex[p->sides - 1], p->vertex[0]);
    for(int i = 0; i< p->sides; i++)
    {
        t = distance(p->vertex[i], p->vertex[i+1]);
        if(s != t) return false;
    }
    return true;
}

/* **************************************************
 * TRIANGLE
 * **************************************************/

/* HEADER */
struct triangle { 
    // Triangles are like polygons, but for sake of this example
    // they have heights (shhh. all polygons have heights)
    struct polygon; 
    float (*height)();
};

// Not triangle struct dependant
float heron_area_formula(float a, float b, float c);
float shoelace_area_formula(struct point p0, struct point p1, struct point p2);


/* Triangle struct dependant functions */

struct triangle * triangle_init(void);

/* First ones from polygon */
void              triangle_destroy(struct triangle *tri);
float             triangle_area(struct triangle * tri);
float             triangle_perimeter(struct triangle * tri);
void              triangle_action(struct triangle *tri);

/* More specilized ones */

/* These two extract the needed information to the non triangle dependant
 * functions
 */
float             triangle_heron_area(struct triangle * tri);
float             triangle_shoelace_area(struct triangle *tri);

/* These are specilized to triangle struct only, not existing in general
 * polygons
 */
float             triangle_height(struct triangle * tri);
float             triangle_height_from_base1(struct triangle *tri);
float             triangle_height_from_base2(struct triangle *tri);
float             triangle_height_from_base3(struct triangle *tri);


/* Functions */

/* Some known formulas to calculate triangle area */

// Calculates triangle area given face three distances
float heron_area_formula(float a, float b, float c)
{
    float p = (a + b + c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));

}

// Calculates triangle area given three vertices
float shoelace_area_formula(struct point p0, struct point p1, struct point p2)
{
    return .5 * fabs(
            p0.x * p1.y -
            p0.y * p1.x +
            p1.x * p2.y -
            p1.y * p2.x +
            p2.x * p0.y -
            p2.y * p0.x);
}

struct triangle * triangle_init(void)
{
    struct triangle * tri;
    tri = malloc(sizeof *tri);
    tri->sides = 3;
    tri->destroy = free;
    tri->action = generic_action;
    tri->perimeter = generic_perimeter;
    tri->area = triangle_heron_area;     // By default we use heron's formula
    tri->height = triangle_height_from_base1; // By default height is related to first 2 points

    return tri;

}

void triangle_destroy(struct triangle *tri)
{
    tri->destroy(tri);
}

float triangle_heron_area(struct triangle * tri)
{
    return heron_area_formula(
            distance(tri->vertex[0], tri->vertex[1]),
            distance(tri->vertex[1], tri->vertex[2]),
            distance(tri->vertex[2], tri->vertex[0]));
}


float triangle_shoelace_area(struct triangle *tri)
{
    return shoelace_area_formula(tri->vertex[0], tri->vertex[1], tri->vertex[2]);
}


float triangle_area(struct triangle * tri)
{
    return tri->area(tri);
}

float triangle_perimeter(struct triangle * tri)
{
    return tri->perimeter((struct polygon *)tri);
}

void triangle_action(struct triangle *tri)
{
    printf("Triangle addr %p: ",(void *)tri);
    printf("Triple action\n");
    tri->action();
    tri->action();
    tri->action();
}


// Height from three bases
float triangle_height_from_base1(struct triangle *tri)
{
    return 2 * triangle_area(tri) / distance(tri->vertex[0], tri->vertex[1]);
}

float triangle_height_from_base2(struct triangle *tri)
{
    return 2 * triangle_area(tri) / distance(tri->vertex[1], tri->vertex[2]);
}

float triangle_height_from_base3(struct triangle *tri)
{
    return 2 * triangle_area(tri) / distance(tri->vertex[2], tri->vertex[3]);
}

// Pick one
float triangle_height(struct triangle * tri)
{
    return tri->height(tri);
}


/* **************************************************
 * SQUARE
 * **************************************************/
struct square
{
    struct polygon;
    float (*height)();
    bool (*is_square)(struct square *s);
};

struct square * square_init(void);
void            square_destroy(struct square *s);
float           square_area(struct square *s);
float           square_perimeter(struct square *s);
void            square_action(struct square *s, int num);
float           square_height(struct square *s);

bool            square_check_by_side(struct square *s);
float           height_from_side(struct square *s);


struct square * square_init(void)
{
    struct square * s;
    s = malloc(sizeof *s);
    s->sides = 4;
    s->destroy = free;
    s->area = null_area;
    s->perimeter = null_perimeter;
    s->action = null_action;
    s->is_square = square_check_by_side; 
    s->height = height_from_side;

    return s;
}

void square_destroy(struct square *s)
{
    s->destroy(s);
}

float square_area(struct square *s)
{
    return s->area(s);
}

float square_perimeter(struct square *s)
{
    return s->perimeter(s);
}

void square_action(struct square *s, int num)
{
    s->action(s);
}

float square_height(struct square * s)
{
    return s->height(s);
}

bool square_check_by_side(struct square *s)
{
    return (bool)((s->sides == 4) && all_sides_are_congruent((struct polygon *) s));
}

float height_from_side(struct square *s)
{
    return distance(s->vertex[0], s->vertex[1]);
}

bool square_check(struct square *s)
{
    return s->is_square(s);
}

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
    p1.perimeter = &generic_perimeter;
    p1.action = &generic_action;
    printf("Perimeter of P1 %.2f\n", polygon_perimeter(&p1));
    polygon_action(&p1);
    printf("\n");


    // Method 2
    struct polygon *p2 = polygon_init(3);
    struct point t[3] = { {0, 0}, {.5, 1}, {1, 0}};
    memcpy(p2->vertex, t, sizeof(t));
    printf("Perimeter of P2 %.2f\n", polygon_perimeter(p2));
    polygon_action(p2);
    polygon_destroy(p2);
    printf("\n");

    // A triangle
    struct triangle *t1 = triangle_init();
    memcpy(t1->vertex, t, sizeof(t));
    printf("Perimeter of T1 %.2f\n", triangle_perimeter(t1));
    printf("Area of T1 %.2f\n", triangle_area(t1));
    t1->area = triangle_shoelace_area;              // Let's use another area formula
    printf("Area of T1 %.2f\n", triangle_area(t1));
    printf("Height of T1 base 1 %.2f\n", triangle_height(t1));
    t1->height = triangle_height_from_base2;
    printf("Height of T1 base 2 %.2f\n", triangle_height(t1));
    t1->height = triangle_height_from_base3;
    printf("Height of T1 base 3 %.2f\n", triangle_height(t1));
    triangle_action(t1);
    triangle_destroy(t1);
    printf("\n");

    // Now a square;
    struct square *s1 = square_init();
    struct point s[4] = { {0, 0}, {0, 1}, {1, 1}, {1, 0} };
    memcpy(s1->vertex, s, sizeof(s));
    printf("Perimeter of S1 %.2f\n", square_perimeter(s1));
    printf("Area of S1 %.2f\n", square_area(s1));
    printf("Height of S1 %.2f\n", square_height(s1));
    printf("Is S1 a square? %s\n", square_check(s1) ? "true":"false");
    printf("Square action\n");
    square_action(s1, 5);


    return 0;
}

