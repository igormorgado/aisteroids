#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

/* A debug view ...

sa = arithmetic_sequence(3,2)
	d = arithmetic_sequence_data{cur = 1, step = 2}
	_RET = sequence__create(arithmetic_sequence__next, d)
		s = Sequence{ next = arithmetic_sequence_next, data = d}

sa = Sequence{next = arithmetic_sequence_next, data = d}
sa->data = {cur = 1, step = 2}
sa->next = arithmetic_sequence_next
sa->data->cur = 1;
sa->data->step = 2;


arithmetic_sequence__next(sa->data)
	d = sa->data
	d->cur = += d->step   ==== sa->data->cur += sa->data->step
	return d->cur === return sa->data->cur

*/

/* a sequence is an object tthat returns a new value each time it is called */
struct sequence {
    int (*next) (void *data);
    void *data;
};

typedef struct sequence *Sequence;

/*
 * GENERIC SEQUENCE
 */
Sequence sequence__create(int (*next)(void * data), void * data)
{
    Sequence s;
    s = malloc(sizeof *s);
    assert(s);

    s->next = next;
    s->data = data;

    return s;
}

int sequence__next(Sequence self)
{
    return self->next(self->data);
}

/*
 * CONSTANT SEQUENCE
 */

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


/*
 * ARITHMETIC SEQUENCE
 */
struct arithmetic_sequence_data {
    int cur;
    int step;
};


static int arithmetic_sequence__next(void *data)
{
    struct arithmetic_sequence_data *d; 

    d = data;
    d->cur += d->step;

    return d->cur;
}

Sequence arithmetic_sequence(int x, int a)
{
    struct arithmetic_sequence_data *d;
    d = malloc(sizeof *d);
    d->cur = x - a;
    d->step = a;

    return sequence__create(arithmetic_sequence__next, d);
}

/*
 * Binary SEQUENCES FUNCTIONS
 */
static int sequences__add_next(void *data)
{
    Sequence *s;

    s = data;
    return sequence__next(s[0]) + sequence__next(s[1]);
}

Sequence sequences__add(Sequence s0, Sequence s1)
{
    Sequence *s;
    s = malloc(2*sizeof(*s));
    if (s == 0)
        return 0;

    s[0] = s0;
    s[1] = s1;

    return sequence__create(sequences__add_next, s);
}

/*
 * ITERATED SEQUENCES FUNCTION
 */

/* returns the sequence x, f(x), f(f(x))...  */
struct iterated_function_sequence_data
{
    int x;
    int (*f)(int);
};

static int iterated_function_sequence__next(void *data)
{
    struct iterated_function_sequence_data *d;
    int retval;

    d = data;

    retval = d->x;
    d->x = d->f(d->x);

    return retval;

}

Sequence iterated_function_sequence(int (*f)(int), int x0)
{
    struct iterated_function_sequence_data *d;

    d = malloc(sizeof *d);
    if (d == 0)
        return 0;

    d->x = x0;
    d->f = f;

    return sequence__create(iterated_function_sequence__next, d);
}

int doubleit(int n)
{
    return 2*n;
}

int main(void)
{
    Sequence sc = constant_sequence(4);
    for (int i = 0; i< 10; i++) 
        printf("Const[%d]: %d\n", i, constant_sequence__next(sc->data));

    Sequence sa = arithmetic_sequence(3,2);
    for (int i = 0; i< 10; i++) 
        printf("Ari(3,2)[%d]: %d\n", i, arithmetic_sequence__next(sa->data));

    Sequence si = iterated_function_sequence(doubleit, 2);
    for (int i = 0; i< 10; i++) 
        printf("iter(doubleit,2)[%d]: %d\n", i, iterated_function_sequence__next(si->data));
    
    return 0;
}
