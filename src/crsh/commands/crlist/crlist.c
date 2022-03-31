#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


void crlist (int *array, char **comandos) 
{
    printf("PID  \tNombre ejecutable  \tTiempo de ejecucion\n");
    for (int i=0; i<300; i+=1)
    {   if (array[i] != 0)
        {
            int status;
            int retorno = waitpid(array[i], &status, WNOHANG);

            if (retorno == 0) //si proceso esta vivo. AQUI TENEMOS QUE IMPRIMIR TABLA
            {
                printf("%i\t%s\n", array[i], comandos[i]);
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
 