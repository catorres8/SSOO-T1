#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "process.h"
#include "../file_manager/manager.h"


Process* process_init(char* name, char* pid, char* t_inicio, char* cycles, char* wait, char* wait_delay, char* s)
{
    Process* proceso = malloc(sizeof(Process));
    *proceso = (Process) {
        .PID = atoi(pid),
        .nombre = name,
        .prioridad = 2,
        .estado = 0,
        .quantum = 0,
        .init_time = atoi(t_inicio),
        .cycles = atoi(cycles),
        .wait = atoi(wait),
        .wait_delay = atoi(wait_delay),
        .s = atoi(s),
        .turnos_cpu = 0,
        .interrupciones = 0,
        .turnaround_time = 0,
        .response_time = 0,
        .waiting_time = 0,  // tiempo en que el proceso ha estado en ready y waiting
        .count_waiting = 0, // Listo
        .count_running = 0, // listo 
        .count_cycles = 0, // listo
        .count_s = 0,      // listo
        .contador_rafagas = 0,
    };

    return proceso;
}



/* Funcion que recive una lista con el detalle de inicio de los procesos y los instancia,
retornando una lista con ellos */
Process** processes_init(InputFile* input_file)
{
    Process** list_process = malloc (sizeof(Process *) * input_file->len);
    for (int i = 0; i < input_file->len; ++i)
    {
        Process* proceso =  process_init(
            input_file->lines[i][0], 
            input_file->lines[i][1], 
            input_file->lines[i][2], 
            input_file->lines[i][3], 
            input_file->lines[i][4], 
            input_file->lines[i][5], 
            input_file->lines[i][6]
        );
        list_process[i] = malloc(sizeof(Process *));
        list_process[i] = proceso;
    }

    return list_process;
}

char* concat_array_strings(char* cadena, char** array_strings, int len_array)
{   
    for (int i = 0; i < (len_array - 1); i++)
    {
        strcat(cadena, array_strings[i]);
        strcat(cadena, ", ");
    }
    strcat(cadena, array_strings[(len_array - 1)]);
    strcat(cadena, "\n");

    //Testeo
    printf("Esta es la concatenacion de datos de un proceso: %s\n", cadena);

    return cadena;
}

char* compile_data(Process* proceso)
{
    /*
    Formato de Salida:
    "nombre,turnos_cpu,interrupciones,turnaround_time,response_time,waiting_time"
    */
    char cadena[4096];
    char buffer[32];

    char **data = calloc(32*6, sizeof(char));

    data[0] = calloc(32, sizeof(char));
    data[0] = proceso->nombre;

    data[1] = calloc(32, sizeof(char));
    sprintf(buffer, "%d", proceso->turnos_cpu);
    data[1] = buffer;

    data[2] = calloc(32, sizeof(char));
    sprintf(buffer, "%d", proceso->interrupciones);
    data[2] = buffer;

    data[3] = calloc(32, sizeof(char));
    sprintf(buffer, "%d", proceso->turnaround_time);
    data[3] = buffer;

    data[4] = calloc(32, sizeof(char));
    sprintf(buffer, "%d", proceso->response_time);
    data[4] = buffer;

    data[5] = calloc(32, sizeof(char));
    sprintf(buffer, "%d", proceso->waiting_time);
    data[5] = buffer;
    
    return concat_array_strings(cadena, data, 6);
}

