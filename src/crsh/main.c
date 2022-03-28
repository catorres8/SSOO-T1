#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../input_manager/manager.h"
#include "commands/hello/hello.h"
#include "commands/sum/sum.h"
#include "commands/prime/prime.h"
#include "commands/crexec/crexec.h"

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
        hello();  //hasta aqui funcionaba
        exit(0);
      }
      else if (a > 0)
      {
        
      //agregamos procesos al arreglo
      int i = 0
      int condicion = 1
      while(condicion == 1)
      {
        if (pid_array[i] == 0)
          {
            pid_array[i] = a //GUARDO pid del proceso
            condicion = 0 
          }
        i += 1
      }
      //
      }
    }
    
    else if (strcmp(input[0],"sum") == 0)
    {
      int a = fork();
      if (a == 0)
      {
        sum(input[1], input[2]);
      }
    }

    else if (strcmp(input[0],"is_prime") == 0)
    {
      int a = fork();
      if (a == 0)
      {
        is_prime(input[1]);
      }
    }

    else if (strcmp(input[0],"crexec") == 0)
    {
      int a = fork();
      if (a == 0)
      {
        crexec(input);
      }
    }

    //else if strcmp(input[0],"crexec") == 0)
    //{}

    else if (strcmp(input[0],"crexit") == 0)
    {
      n = 0;

      while (int i = 0; i < 300)
      {
        waitpid(pid_array[i], &status, );
      }
      
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