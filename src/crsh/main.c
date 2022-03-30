/* LIBRERIAS */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../input_manager/manager.h"
#include "commands/hello/hello.h"
#include "commands/sum/sum.h"
#include "commands/prime/prime.h"
#include "commands/crexec/crexec.h"
#include "commands/crlist/crlist.h"
#include "commands/crexit/crexit.h"


/* VAR GLOBALES */
int *pid_array;

/* FUNCIONES */
int pid_append (int pid_num, int *pid_array)
{
  int i = 0;
  while(i < 300)
  {
    if (pid_array[i] == 0)
      {
        pid_array[i] = pid_num; //GUARDO PID del proceso
        i = 300;
      }
    i += 1;
  }
  return 0;
}

void sigHandler(int signum) 
{
  exit(1);
}

void sigHandlerMain(int signum) 
{
  crexit(pid_array);
  exit(0);
}


/* MAIN */
int main(int argc, char const *argv[])
{
  //Manejo de SIGINT para 'main'
  signal(SIGINT, sigHandlerMain);
  
  int *pid_array = calloc(300, sizeof(int)); //definimos un arreglo

  int n = 1;
  while (n == 1)
  {
    printf("> ");
    //char A[50][3]; // Creacion arreglo para guardar informacion de los programas ejecutando

    char **input = read_user_input();

    // HELLO
    if (strcmp(input[0],"hello") == 0) 
    {
      int a = fork();
      if (a == 0)
      {
        //Manejo de SIGINT
        signal(SIGINT, sigHandler);

        hello();
      }
      else if (a > 0)
      {
        // Agregamos procesos al arreglo
        pid_append(a, pid_array);
      }
    }
    
    // SUM
    else if (strcmp(input[0],"sum") == 0)
    {
      int a = fork();
      if (a == 0)
      {
        //Manejo de SIGINT
        signal(SIGINT, sigHandler);

        sum(input[1], input[2]);
      }
      else if (a > 0)
      {
        // Agregamos procesos al arreglo
        pid_append(a, pid_array);
      }
    }

    // IS_PRIME
    else if (strcmp(input[0],"is_prime") == 0)
    {
      int a = fork();
      if (a == 0)
      {
        //Manejo de SIGINT
        signal(SIGINT, sigHandler);

        is_prime(input[1]);
      }
      else if (a > 0)
      {
        // Agregamos procesos al arreglo
        pid_append(a, pid_array);
      }
    }

    // CREXEC
    else if (strcmp(input[0],"crexec") == 0)
    {
      int a = fork();
      if (a == 0)
      {
        crexec(input);
      }
      else if (a > 0)
      {
        // Agregamos procesos al arreglo
        pid_append(a, pid_array);
      }
    }

    // CRLIST
    else if (strcmp(input[0],"crlist") == 0)
    {
      crlist(pid_array);
    }

    // CREXIT
    else if (strcmp(input[0],"crexit") == 0)
    {
      crexit(pid_array);

      free_user_input(input);       
      exit(0);
    }

    else
    {
      printf("Ingrese un comando valido\n");
    }

    free_user_input(input);
  }
}
