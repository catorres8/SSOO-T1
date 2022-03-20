#include <stdio.h>

#include "../input_manager/manager.h"

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



Cosas por hacer:
- Averiguar como funcionan los punteros.
- Hacer el manejo de strings (if ... ) (*averiguar manera de manejar numeros inputs, raul)
- modularizar los comandos.