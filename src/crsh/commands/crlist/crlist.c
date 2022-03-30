#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


void crlist (int *array) 
{
    for (int i=0; i<300; i+=1)
    {   if (array[i] != 0)
        {
            int status;
            printf("imprimiremos el array probando (dentro de crlist) %d\n", array[i]);
            int retorno = waitpid(array[i], &status, WNOHANG);
            printf("Error: %s\n", strerror(errno));

            if (retorno == 0) //si proceso esta vivo. AQUI TENEMOS QUE IMPRIMIR TABLA
            {
                printf("esto es el PID que entrega variable retorno =  %i\n", retorno);
                printf("esto es el nombre del ejecutable o sea el comando =  %s\n", array[0]);
            }
            else
            {
                printf("Esto es lo que entrega la variable retorno = %i\n", retorno);
                printf("el proceso esta muerto \n");
            }
        }
        else
        {
            break;
        }

    }
}


//recorremos arreglo:
//    hacemos waitpid por cada elemento
//    if elemento = vivo:
//         imprimir: pid   nombre ejec   tiempo    
 