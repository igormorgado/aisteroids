#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Structs
typedef struct mystring mystring;
struct mystring
{
    char * chars;
    int (*length)(mystring*);
};


// Prototypes
mystring * mystring__init(int n);
void       mystring__destroy(mystring * self);
int        length(mystring * self);


// Function declarations
int length(mystring * self)
{
    return strlen(self->chars);
}


mystring * mystring__init(int n)
{
    mystring *str;
    str = malloc(sizeof *str);
    str->chars = malloc(n);
    str->length = length;
    str->chars[0] = '\0';

    return str;
}


void mystring__destroy(mystring * self)
{
    free(self->chars);
    free(self);
}


// Main
int main(void)
{
    mystring *p = mystring__init(30);
    strcpy(p->chars, "Hello");
    printf("%s : %d\n", p->chars, p->length(p));
    mystring__destroy(p);
    return 0;
}


