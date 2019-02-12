#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct counter counter_st;

struct counter
{
    int i1;
    int i2;
};

int main(void)
{
    counter_st * cnt = malloc(sizeof *cnt); 
    memset(cnt, 0, sizeof *cnt);
    cnt->i1 = 1000;
    printf("%d\n", cnt->i1);
    cnt->i1++;
    printf("%d\n", cnt->i1);
    --cnt->i1;
    printf("%d\n", cnt->i1);
    cnt->i1--;
    printf("%d\n", cnt->i1);
    ++cnt->i1;
    printf("%d\n", cnt->i1);


    return 0;
}

