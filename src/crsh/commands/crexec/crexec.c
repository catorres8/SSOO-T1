#include <unistd.h> // se importa para el excecl
#include<stdio.h>  // se importa para el stat
#include<sys/stat.h> // se importa para el stat


void crexec (char **inputs) 
{
    char *exeName = inputs[1]; //ruta del archivo binario ejecutable    
    char **args =  inputs + 1; //argumento que desea pasar al ejecutable

    int exe = execv(exeName, args);
    printf("Error: El archivo no existe - %i", exe);
}
