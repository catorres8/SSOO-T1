#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>



void crexit (int *pid_array)
{
    // Envio de la signal SIGNINT
    printf("\nInicia el cierre de './crsh'\n");
    for (int i = 0; i < 300; i++)
    {
        if (pid_array[i] != 0)
        {
            kill(pid_array[i], SIGINT);
        }
    }

    // Wait de los procesos que hayan terminado
    for (int j = 0; j < 300; j++)
    {
        if (pid_array[j] != 0)
        {
            int status;
            waitpid(pid_array[j], &status, WNOHANG);
        }        
    }
    
    // Espera de 15 segundos de los procesos.
    sleep(15);

    for (int k = 0; k < 300; k++)
    {
        if (pid_array[k] != 0)
        {
            int status;
            int alive = waitpid(pid_array[k], &status, WNOHANG);
            if (alive == 0)
            {
                kill(pid_array[k], SIGKILL);
                waitpid(pid_array[k], &status, WNOHANG);
            }
        }
    }
    printf("Finaliza el cierre de './crsh'\n");
}
