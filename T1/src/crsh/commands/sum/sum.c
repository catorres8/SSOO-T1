#include <stdio.h>
#include <stdlib.h>
// Funcion sum se encarga de sumar los argumentos entregados y 
// retornar el  mensaje respectivo
void sum(char* a, char* b)
{
    float x = atof(a);
    float y = atof(b);
    float c = x + y;
    printf("La suma de %f y %f es %f\n", x, y, c);
}