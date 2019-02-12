#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

const int vsize = 5;     // Vector total size
const int fsize = 2;     // Float precision size

#define debug_print(fmt, ...)					\
	do {							\
		if (DEBUG)					\
			fprintf(stderr, "%s:%d:%s() " fmt,	\
					__FILE__,		\
					__LINE__,		\
					__func__,		\
					__VA_ARGS__);		\
	} while(0)						\

#define debug_print_body_fmt(body) do { char *s = body_fmt(body) ;  debug_print("%s\n", s); free(s); } while(0)

struct vector {
	float x;
	float y;
	float z;
};

struct body {
	struct vector * vector;
	float  mass;
	char name[5];
};

char * vector_fmt(struct vector * vector)
{
    char * s;
    const int nsize = 3;     // Number of elements in vector
    const int tsize = (nsize * (vsize + 1)) + (2 * (nsize - 1));

    s = malloc(tsize + 1);
    snprintf(s, tsize, "%*.*f, %*.*f, %*.*f", 
            vsize, fsize, vector->x,
            vsize, fsize, vector->y,
            vsize, fsize, vector->z);

    return s;
	    
}

char * body_fmt(struct body * body)
{

	char * s;
	const int nsize = 1;
   	const int psize = (3 * (vsize + 1)) + 4;
   	const int tsize = (nsize * (vsize + 1)) + (2 * (nsize - 1)) + psize + 11;
	s = malloc(tsize + 1);

	char *t = vector_fmt(body->vector);
	snprintf(s, tsize, "%5s: %*.*fg (%s)",
			body->name, vsize, fsize, body->mass, t);

	free(t);
	
	return s;
}


int main(void)
{
	struct vector v1 = { .x = 2, .y = 3.1, .z = 0.5 };
	struct body b1 = { &v1, 3.2, "FOO" };

	// This defeats the whole purpose of a single command debug print
	debug_print_body_fmt(&b1); 
	debug_print_body_fmt(&b1); 
	debug_print_body_fmt(&b1); 
	
	// What I would like is something like:
	// debug_print("%s\n", body_fmt(&b1));
	// Unfortunately this leads to leaks
	
	
	return 0;
}

