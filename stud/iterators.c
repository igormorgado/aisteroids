#ifndef __NUMS_H__
#define __NUMS_H__
/*
 * nums.h
 *
 * Abstract data type representing the set of numbers 0 to bound-1 inclusive,
 * where bound is passed in as an argument at creation
 */
typedef struct nums *Nums;
/* Constructor */
Nums nums__create(int bound);

/* Destructor */
void nums__destroy(Nums);

/* Returns 1 if nums contains element, and 0 otherwise */
int nums__contain(Nums nums, int element);

/* Returns all elements of nums */
int * nums__contents(Nums self);

/* Returns the first element of a sequence */
int nums__first(Nums self);

/* Returns 0 if reached the last element, 1 otherwise */
int nums__done(Nums self, int val);

/* Returns the next element of a sequence */
int nums__next(Nums self, int val);

/* A custom foreach to nums structure */
void nums__foreach(Nums self, void (*f)(int, void*), void *f_data);

/* Accumulates the sum into f_data */
static void sum_helper(int i, void *f_data);
#endif

/*
 * nums.c
 */

#include <stdlib.h>
#include <stdio.h>
// #include "nums.h" 

struct nums {
    int bound;
};

Nums nums__create(int bound)
{
    struct nums *n;
    n = malloc(sizeof *n);
    n->bound = bound;
    return n;
}

void nums__destroy(Nums self)
{
    free(self);
}

int nums__contains(Nums self, int element)
{
    return element >= 0 && element < self->bound;
}

int * nums__contents(Nums self)
{
    int *a = malloc(sizeof (*a) * (self->bound + 1));

    for(int i = 0; i < self->bound; i++)
        a[i] = i;

    a[self->bound] = -1;

    return a;
}

int nums__first(Nums self)
{
    return 0;
}

int nums__done(Nums self, int val)
{
    return val >= self->bound;
}

int nums__next(Nums self, int val)
{
    return val+1;
}

void nums__foreach(Nums self, void (*f)(int, void*), void *f_data)
{
    for(int i = 0; i < self->bound; i++)
        f(i, f_data);
}

static void sum_helper(int i, void *f_data)
{
    *((int *) f_data) += i;
}

/*
 * main.c
 */

int main(void) 
{
    const int to = 10;
    int sum;
    Nums nums = nums__create(to);

    /* Iterating in contents */
    sum = 0;
    int *contents = nums__contents(nums);
    int *p;
    for(p = contents; *p != -1; p++)
        sum += *p;

    printf("The sum to %d is %d\n", to-1, sum);
    free(contents);
    /* END: Iterating in contents */

    /* Iterating using first,done,next */
    sum = 0;
    int i;
    for(i = nums__first(nums); !nums__done(nums, i); i = nums__next(nums, i)) {
        sum += i;
    }
    printf("The sum to %d is %d\n", to-1, sum);
    /* END: Iterating using first,done,next */

    /* Iterating using custom function */
    sum = 0;
    nums__foreach(nums, sum_helper, (void *) &sum);
    printf("The sum to %d is %d\n", to-1, sum);

    nums__destroy(nums);
    return 0;
}
