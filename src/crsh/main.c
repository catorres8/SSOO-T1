#include <stdio.h>

#include "../input_manager/manager.h"

int main(int argc, char const *argv[])
{
  printf("> ");
  char **input = read_user_input();
  printf("> The first argument you wrote was: %s\n", input[0]);
  free_user_input(input);
}
