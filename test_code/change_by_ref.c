#include <stdio.h>

int muda(int *a)
{
    *a += 10;
}

int main(void)
{
    int *p;
    int v = 5;
    p = &v;
    printf("Antes %d\n", *p);
    muda(p);
    printf("Depois %d\n", *p);
    return 0;
}
