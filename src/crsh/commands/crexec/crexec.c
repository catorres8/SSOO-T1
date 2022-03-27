#include <unistd.h> // se importa para el excecl
#include<stdio.h>  // se importa para el stat
#include<sys/stat.h> // se importa para el stat


void crexec (char* ejecutable, char* input) 
{
    char * binaryPath = ejecutable ; //ruta del archivo binario ejecutable
    char * arg1 = input ; //argumento que desea pasar al ejecutable
    
    //printf("Eeste es el input , o sea el argumento :D - %i", *arg1);

    int exe = execl ( binaryPath , input , NULL );
    printf("Error: El archivo no existe - %i", exe);
       
}
