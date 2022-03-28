#include <stdio.h>
#include <sys/wait.h>

void crlist () 
{
    for (int i=0; i<300; i+=1)
    {
        int retorno = waitpid(pid_array[i], &status, WNOHANG);
        if (retorno == 0) //si proceso esta vivo
        {
            printf("esto es el PID que entrega variable retorno =  %i\n", retorno)
        }

    }
}


//recorremos arreglo:
//    hacemos waitpid por cada elemento
//    if elemento = vivo:
//         imprimir: pid   nombre ejec   tiempo    
 