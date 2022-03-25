#include <unistd.h> // se importa para el excecl
#include<stdio.h>  // se importa para el stat
#include<sys/stat.h> // se importa para el stat


char crexec (char ejecutable, char input) 
{
    if (checkIfFileExists(ejecutable))
    {
        char * binaryPath = ejecutable ; //ruta del archivo binario ejecutable
        char * arg1 = input ; //argumento que desea pasar al ejecutable
    
        execl ( binaryPath , arg1 , NULL ) ;
    }
    
    else
    {
      printf("Error: El archivo no existe")  
    }    
}


int checkIfFileExists(const char* ejecutable){
    struct stat buffer;
    int exist = stat(ejecutable,&buffer);
    if(exist == 0)
        return 1;
    else  
        return 0;
}

// REFERENCIA:
// https://www.delftstack.com/es/howto/c/c-check-if-file-exists/#:~:text=completa%20del%20archivo.-,stat()%20Funci%C3%B3n%20para%20comprobar%20si%20un%20archivo%20existe%20en,si%20el%20archivo%20no%20existe.&text=El%20programa%20imprimir%C3%A1%20file%20exists%20si%20el%20archivo%20demo


//Defina la función: int stat (const char * file_name, struct stat * buf);
//Descripción de la función: stat () se utiliza para copiar el estado del archivo señalado por el parámetro file_name a la estructura señalada por el parámetro buf.