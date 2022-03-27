#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../input_manager/manager.h"
#include "commands/hello/hello.h"
#include "commands/sum/sum.h"
#include "commands/prime/prime.h"
#include "commands/crexec/crexec.h"

int main(int argc, char const *argv[])
{
  int n = 1;
  while (n == 1)
  {
    printf("> ");
    //char A[50][3]; // Creacion arreglo para guardar informacion de los programas ejecutando

    char **input = read_user_input();

    if (strcmp(input[0],"hello") == 0) 
    {
      int a = fork();
      if (a ==0)
      {
        hello();
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
        crexec(input[1], input[2]);
      }
    }

    else if (strcmp(input[0],"crexit") == 0)
    {
      n = 0;
    }

    else
    {
      printf("Ingrese un comando valido");
    }

    free_user_input(input);
  }
}