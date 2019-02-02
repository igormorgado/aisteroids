#include <stdlib.h>
#include <stdio.h>

/* Preprocessor cheats */
#define COUNTER_FIELDS \
    void (*reset)  (struct counter *); \
    int  (*next)   (struct counter *); \
    void (*destroy)(struct counter *);

struct counter {
    COUNTER_FIELDS
};

typedef struct counter Counter;

/* minimal counter--always returns zero */
/* we don't even alllocate this, just have a global one */
static void noop(Counter * c){
    ;
}

static int return_zero(Counter * c)
{
    return 0;
}

static struct counter Zero_counter = { noop, return_zero, noop };

Counter * make_zero_counter(void)
{
    return &Zero_counter;
}

/*
 * a fancier counter that iterates a functiton sequence
 * this struct is not exported anywhere
 */
struct ifs_counter {
    COUNTER_FIELDS

    /* New fields */
    int init;
    int cur;
    int (*f)(int);
};

static void ifs_reset(Counter * self)
{
    struct ifs_counter *ic;

    /* Here happens a cast in `self` to address memory correctly since
     * ifs_counter is bigger than Counter otherwise we will move wrongly
     * or even do not find some structure internal data
     */
    ic = (struct ifs_counter *) self;

    ic->cur = ic->init;
}

static int ifs_next(Counter * self)
{
    struct ifs_counter *ic;
    int ret;

    /* Here happens a cast in `self` to address memory correctly since
     * ifs_counter is bigger than Counter otherwise we will move wrongly
     * or even do not find some structure internal data
     */
    ic = (struct ifs_counter *) self;

    ret = ic->cur;
    /* Here we apply f to ic->cur to recursively store the next
     * value into ic->cur based on value returned from  `f(x)`
     */
    ic->cur = ic->f(ic->cur);

    return ret;
}

static void ifs_destroy(Counter * self) {
    free(self);
}

Counter * ifs_create(int init, int (*f)(int))
{
    struct ifs_counter *ic;

    ic = malloc(sizeof *ic);

    ic->reset = ifs_reset;
    ic->next = ifs_next;
    // ic->destroy = (void (*)(struct counter *)) free;
    ic->destroy = ifs_destroy;

    ic->init = init;
    ic->cur = init;
    ic->f = f;

    /* it's always a counter on the outside */
    return (Counter *) ic;
}

static int times2(int x)
{
    return x*2;
}

void print_powers_of_2(void)
{
    Counter * c = ifs_create(1, times2);

    for(int i = 0; i < 10; i++)
        printf("%d %d\n", i, c->next(c));

    c->reset(c);
    for(int i = 0; i < 20; i++)
        printf("%d %d\n", i, c->next(c));

    c->destroy(c);
}

int main(void)
{
    print_powers_of_2();

    return 0;
}
