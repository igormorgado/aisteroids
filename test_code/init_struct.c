#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
struct params
{
    int a;
    int b;
    float c;
};

struct base
{
    int a;
    int b;
    float c;
};

struct base * base_ctor(void)
{
    struct base * self = malloc(sizeof *self);
    return self;
}

void base_init(struct base * self, struct base params)
{
    self->b = params.b;
    self->c = params.c;
    self->a = params.a;
}

void base_print(struct base * self)
{
    printf("BASE %p a: %d b: %d c: %f\n", (void*)self, self->a, self->b, self->c);
}

void base_dtor(struct base * self)
{
    //
}

void base_free(struct base * self)
{
    free(self);
}


int main(void)
{
    struct base params = { .a = 4 };

    struct base * mbase = base_ctor();
    base_init(mbase, params);
    base_print(mbase);
    base_dtor(mbase);
    base_free(mbase);

    return 0;
}

