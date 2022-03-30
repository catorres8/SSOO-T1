#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


void crlist (int *array, char *comandos) 
{
    printf("PID    Nombre ejecutable    Tiempo de ejecucion\n");
    for (int i=0; i<300; i+=1)
    {   if (array[i] != 0)
        {
            int status;
            int retorno = waitpid(array[i], &status, WNOHANG);
            printf("ESTO ES RETORNO DEL WAITPUD  %i\n", retorno);
            printf("Error: %s\n", strerror(errno));

            if (retorno == 0) //si proceso esta vivo. AQUI TENEMOS QUE IMPRIMIR TABLA
            {
                printf("hola");
                printf("%i    %s\n", retorno, comandos[i]);
                printf("esto es el nombre del ejecutable o sea el comando =  %s\n", comandos[i]);
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
 