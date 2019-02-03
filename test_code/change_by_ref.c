#include <stdio.h>

int change(int *a)
{
    *a += 10;
}

int main(void)
{
    int *p;
    int v = 5;
    p = &v;
    printf("Before %d\n", *p);
    change(p);
    printf("After %d\n", *p);
    return 0;
}
