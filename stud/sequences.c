#include <stdlib.h>
#include <stdio.h>

/* a sequence is an object tthat returns a new value each time it is called */
struct sequence {
    int (*next) (void *data);
    void *data;
};

typedef struct sequence *Sequence;

Sequence sequence__create(int (*next)(void * data), void * data)
{
    Sequence s;
    s = malloc(sizeof *s);

    s->next = next;
    s->data = data;

    return s;
}

int sequence__next(Sequence self)
{
    return self->next(self->data);
}

static int constant_sequence__next(void *data)
{
    return *((int *) data);
}

Sequence constant_sequence(int x)
{
    int *data;
    data = malloc(sizeof *data);
    if (data==0) return 0;
    *data = x;
    return sequence__create(constant_sequence__next, data);
}


int main(void)
{
    Sequence sc = constant_sequence(4);
    for (int i = 0; i< 10; i++) 
        printf("Const[%d]: %d\n", i, constant_sequence__next(sc->data));
    
    return 0;
}
