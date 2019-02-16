#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "common.h"


void *
smalloc(size_t n)
{
	void *p = malloc(n);
	if (p != NULL) {
		return p;
	} else {
		fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", n);
		abort();
	}
}

void *
sfree(void * p)
{
	if (p != NULL) {
		free(p);
	} else {
		debug_print("%s at %p\n", 
				"Null pointer dereferencing catched",
				__builtin_return_address(0));
	}
	return NULL;
}
