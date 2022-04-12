// Tells the compiler to compile this file once
#pragma once
#include "../file_manager/manager.h"

// Define compile-time constants

// Define the struct
typedef struct process
{
    int PID;
    char* nombre;
    int prioridad;
    int estado; //0=READY; 1=RUNNING; 2=WAITING; 3=FINISHED
    int quantum;
    
    /* INPUT-DATA */
    int init_time;
    int cycles;
    int wait;
    int wait_delay;
    int s;

    /* OUTPUT-DATA */
    int turnos_cpu;
    int interrupciones;
    int turnaround_time;
    int response_time;
    int waiting_time;

    /* Contadores */
    int count_waiting;
    int count_running;
    int count_cycles;
    int count_s;
    int contador_rafagas;
} Process;

// Declare functions
Process* process_init(char* name, char* pid, char* t_inicio, char* cycles, char* wait, char* wait_delay, char* s);
Process** processes_init(InputFile* input_file);
char* compile_data(Process* proceso);