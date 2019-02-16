#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
	float x;
	float y;
};

struct circle {
	struct point origin;
	float radius;
};

struct circle * circle__init(void);
void circle__move(struct circle * c, struct point * v, struct circle * r);
void circle__print(struct circle * c);


struct circle *
circle__init(void)
{
	struct circle * c = malloc(sizeof (*c));
	return c;
}

void 
circle__move(struct circle * c, struct point * v, struct circle * r)
{
	r->origin.x = c->origin.x + v->x;
	r->origin.y = c->origin.y + v->y;
	r->radius = c->radius;
}

void
circle__print(struct circle * c)
{
       printf("circle (%f,%f,%f)\n", 
       		c->origin.x, 
       		c->origin.y, 
       		c->radius);
}

int main(void)
{
	struct point vector = { .x = 1, .y=2 };
	struct circle * circle = circle__init();
	*circle = (struct circle) { .origin.x = 1, .origin.y=2, .radius=3 };
	circle__print(circle);
	circle__move(circle, &vector, circle);
	circle__print(circle);
	free(circle);
	return 0;
}
