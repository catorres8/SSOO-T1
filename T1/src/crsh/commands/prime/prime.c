#include <stdio.h>
#include <stdlib.h>

// Un numero es primo solo si es divisible por 1 y por si mismo
void is_prime(char* a)
{
    int x = atoi(a);

    // Caso de numero invalido
    if (x < 2)
    {
        printf("El numero entregado no es primo\n");
        return;
    }

    // Caso de x = 2
    else if (x == 2)
    {
        printf("El numero entregado es primo\n");
        return;
    }
    
    // Caso de cualquier otro numero
    else if (x > 2)
    { 
        // Bucle que determina si el numero es divisible por algun numero
        // entre 2 y n-1
        for (int i = 2; i < x; i++)
        {
            if (x%i == 0)
            {
                printf("El numero entregado no es primo\n");
                return;
            }
        }
    }
    printf("El numero entregado es primo\n");
}
