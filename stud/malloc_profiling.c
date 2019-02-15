#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXITER 1
#define MAXOPER 10000

struct point {
	float x;
	float y;
};

struct circle {
	struct point origin;
	float radius;
};

struct circle * circle__init(struct circle params);
void circle__move(struct circle * c, struct point * v, struct circle * r);
void circle__print(struct circle * c);
void circle_local(void);
void circle_ptr1(struct circle * params);
void circle_ptr2(struct circle * params);
void circle_ptr3(struct circle * params);


struct circle *
circle__init1(struct circle params)
{
	struct circle * c = malloc(sizeof (*c));
	memcpy(c, &params, sizeof *c);			/* Option 1 */
	return c;
}

struct circle *
circle__init2(struct circle params)
{
	struct circle * c = malloc(sizeof (*c));
	c->radius = params.radius;
	memcpy(&c->origin, &params.origin, sizeof(struct point));
	return c;
}

struct circle *
circle__init3(struct circle params)
{
	struct circle * c = malloc(sizeof (*c));
	c->radius = params.radius;
	c->origin.x = params.origin.x;
	c->origin.y = params.origin.y;
	return c;
}
void 
circle__move(struct circle * c, struct point * v, struct circle * r)
{
	r->origin.x = c->origin.x + v->x;
	r->origin.y = c->origin.y + v->y;
	r->radius = c->radius;
	// circle__print(r);
}

void
circle__print(struct circle * c)
{
       printf("circle (%f,%f,%f)\n", 
       		c->origin.x, 
       		c->origin.y, 
       		c->radius);
}

void
circle_local(void)
{
	struct point vector = { .x = 1, .y=2 };
	struct circle circle = { .origin.x = 1, .origin.y=2, .radius=3 };
	// struct circle res = { .origin.x = 0, .origin.y=0, .radius=0 };
	for(int i = 0; i< MAXOPER; i++)
		circle__move(&circle, &vector, &circle);
	// circle__print(&circle);
}

void
circle_ptr1(struct circle * param)
{

	struct point vector = { .x = 1, .y=2 };
	struct circle * circle = circle__init1(*param);
	// struct circle * res = malloc(sizeof *res);
	for(int i = 0; i< MAXOPER; i++)
		circle__move(circle, &vector, circle);
	// circle__print(circle);
	// free(res);
	free(circle);
}

void
circle_ptr2(struct circle * param)
{

	struct point vector = { .x = 1, .y=2 };
	struct circle * circle = circle__init2(*param);
	// struct circle * res = malloc(sizeof *res);
	for(int i = 0; i< MAXOPER; i++)
		circle__move(circle, &vector, circle);
	// circle__print(circle);
	// free(res);
	free(circle);
}

void
circle_ptr3(struct circle * param)
{

	struct point vector = { .x = 1, .y=2 };
	struct circle * circle = circle__init3(*param);
	// struct circle * res = malloc(sizeof *res);
	for(int i = 0; i< MAXOPER; i++)
		circle__move(circle, &vector, circle);
	// circle__print(circle);
	// free(res);
	free(circle);
}


int main(void)
{
	struct circle param = { .origin.x = 1, .origin.y=2, .radius=3 };

	// for(int i=0; i< MAXITER; i++) 
		circle_local();
	// printf("\n");

	// for(int i=0; i< MAXITER; i++) 
		circle_ptr1(&param);
	// printf("\n");

	// for(int i=0; i< MAXITER; i++) 
		circle_ptr2(&param);
	//printf("\n");
	
	// for(int i=0; i< MAXITER; i++)
		circle_ptr3(&param);
	// printf("\n");

	return 0;
}
