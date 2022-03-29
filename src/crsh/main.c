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


int pid_append (int pid_num)
{
  int i = 1;
  int guardado = 0; // Variable para realizar debug
  while(i < 300)
  {
    if (pid_array[i] == 0)
      {
        pid_array[i] = pid_num; //GUARDO pid del proceso
        guardado = 1;
      }
    i += 1;
  }

  // if (guardado == 0)
  // {
  //  /Posible error al sobrepasar el stack de pid??
  // }

  return 0;
}

void sigHandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);
   exit(1);
}


int main(int argc, char const *argv[])
{

  int *pid_array = calloc(300, sizeof(int)); //definimos un arreglo

  int n = 1;
  while (n == 1)
  {
    printf("> ");
    //char A[50][3]; // Creacion arreglo para guardar informacion de los programas ejecutando

    char **input = read_user_input();

    if (strcmp(input[0],"hello") == 0) 
    {
      int a = fork();
      
      if (a == 0)
      {
        signal(SIGINT, sigHandler);
        hello();  //hasta aqui funcionaba
      }
      else if (a > 0)
      {
        //agregamos procesos al arreglo
        pid_append(a);
      }
    }
    
    else if (strcmp(input[0],"sum") == 0)
    {
      int a = fork();
      if (a == 0)
      {
        signal(SIGINT, sigHandler);
        sum(input[1], input[2]);
      }
      else
      {
        //agregamos procesos al arreglo
        pid_append(a);
      }
    }

    else if (strcmp(input[0],"is_prime") == 0)
    {
      int a = fork();
      if (a == 0)
      {
        signal(SIGINT, sigHandler);
        is_prime(input[1]);
      }
      else
      {
        //agregamos procesos al arreglo
        pid_append(a);
      }
    }

    else if (strcmp(input[0],"crexec") == 0)
    {
      int a = fork();
      if (a == 0)
      {
        signal(SIGINT, sigHandler);
        crexec(input);
      }
      else
      {
        //agregamos procesos al arreglo
        pid_append(a);
      }
    }

    //else if strcmp(input[0],"crlist") == 0)
    //{}

    else if (strcmp(input[0],"crexit") == 0)
    {
      n = 0;

      while (int i = 0; i < 300)
      {
        kill(pid_array[i], SIGINT);
      }
      sleep(15)
      
      
    }

    else
    {
      printf("Ingrese un comando valido\n");
    }

    free_user_input(input);
  }
}

// FORMATO DE IMPRESION CRLIST
// "PID | NOMBRE | TIEMPO"
// "%d | %s | %f\n"