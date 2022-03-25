#include <stdio.h>

#include "../input_manager/manager.h"
#include "../commands/hello/hello.h"
#include "../commands/sum/sum.h"
#include "../commands/prime/prime.h"

int main(int argc, char const *argv[])
{
  int n = 1;
  while (n==1){
    
  }

  printf("> ");
  //
  // int processCounter = 0;
  char A[50][3]; // Creacion arreglo para guardar informacion de los programas ejecutando
  //
  char **input = read_user_input();
  
  if (input=="hello") 
  {
    hello()
  }
  else if (input == "sum")
  {
    sum(input[1], input[2]); 
  }
  else if (input == "is_prime")
  {
    prime(input[1]); 
  }
  else if (input == "crexec")
  {
    crexec(input[1], input[2]); 
  }
  else if (input == "crlist")
  {
    
  }
  else if (input == "crexit")
  {
    // llamada a funcion
    n = 0;
  }
  else
  {
    printf("Ingrese un comando valido");
  }
  
  free_user_input(input);
}
