#include <stdio.h>

#include "../input_manager/manager.h"
#include "../commands/hello/hello.h"
#include "../commands/sum/sum.h"
#include "../commands/prime/prime.h"

int main(int argc, char const *argv[])
{
  printf("> ");
  char **input = read_user_input();
  
  if (input=="hello") 
  {
    
  }
  else if ()
  {
    
  }
  else if ()
  {
    
  }
  else if ()
  {
    
  }
  else if ()
  {
    
  }
  else if ()
  {
    
  }
  else
  {
    printf("Ingrese un comando valido");
  }
  
  free_user_input(input);
}
