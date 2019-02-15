#include <stdio.h>

int main(void) {
    enum diasdasemana {
        Dom,
        Seg,
        Ter,
        Qua,
        Qui,
        Sex,
        Sab
    };

    enum diasdasemana ds;
    int a;

    ds = Qua;
    a = Qui;


    printf("Dia %d\n", ds);
    printf("Domingo %d\n", Dom);
    printf("Dia a  %d\n", a);

    ds = 9;
    printf("Dia 9? %d\n", ds);

    a = 11;
    printf("Dia 11 a?  %d\n", a);

    enum diasdasemana Des = 10;
    enum diasdasemana Inv = 99;

    printf("DesDia %d\n", Des);
    printf("InvDia %d\n", Inv);

    return 0;
}
