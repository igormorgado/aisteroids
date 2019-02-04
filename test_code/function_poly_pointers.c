#include <stdio.h>
#include <stdlib.h>
#include <math.h>



typedef struct ponto P;
struct ponto {
    float x;
    float y;
};

typedef struct poligono POL;
struct poligono
{
    int lados;
    struct ponto vertice[20];
    int (*area)(void);
    int (*perimetro)(void);
    int (*acao)(void);
};

typedef struct triangulo TRI;
struct triangulo
{
    struct poligono;
    int (*altura)(void);
};

typedef struct quadrado QUA;
struct quadrado
{
    struct poligono;
    int (*altura)(void);
};

inline float distancia(struct ponto p1, struct ponto p2);
       
float distancia(struct ponto p1, struct ponto p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int perimetro(struct)
{
    for (int i = 0; i <  
}

int main(void)
{
    POL p1;
    
    p1.lados = 3;
    p1.vertice[0] = (P){ .x = 0, .y = 0 };
    p1.vertice[1].x = 1;
    p1.vertice[1].y = 0;
    p1.vertice[2] = (P){ .5, 1 };

    printf("D %.2f\n", distancia(p1.vertice[1], p1.vertice[2]));

    return 0;
}

