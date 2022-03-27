#include <stdio.h>
#include <stdlib.h>

// Un numero es primo si solo es divisible por 1 y por si mismo
void is_prime(char* a)
{
    int x = atoi(a);
    
    //char mensaje[] = "";
    char *mensaje = malloc(sizeof(char));
    printf("primer mensajito = %s\n", mensaje);
    // Caso de numero invalido
    if (x < 2)
    {
        char mensaje[] = "El numero entregado no es primo";
    }

    // Caso de numero par distinto de 2
    else if (x != 2 && x % 2 == 0)
    {
        char mensaje[] = "El numero entregado no es primo";
    }
    
    // Caso de x = 2
    else if (x == 2)
    {
        char mensaje[] = "El numero entregado es primo";
    }
    
    // Caso de numero no par
    else if (x > 2)
    { 
        // Bucle que determina si el numero es divisible por algun numero
        // entre 2 y n-1
        char mensaje[] = "El numero entregado es primo";
        printf("esto es el mensajito de es primo=%s\n", mensaje);
        for (int i = 2; i < x; i++)
        {
            if (x%i == 0)
            {
                printf("esto es el mensajito1 de no es primo=%s\n", mensaje);
                char mensaje[] = "El numero entregado no es primo";
                printf("esto es el mensajito2 de no es primo=%s\n", mensaje);
                break;
            }
        }
    }
    printf("este es el ultimo mensaje :)%s\n", mensaje);

}
