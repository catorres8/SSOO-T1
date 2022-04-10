// Tells the compiler to compile this file once
#pragma once
#include "../file_manager/manager.h"

// Define compile-time constants


// Define the struct
typedef struct process
{
    int PID;
    char nombre[32];
    int prioridad;
    int estado; //0=READY; 1=RUNNING; 2=WAITING; 3=FINISHED // enum
    int q;
    
    /* INPUT-DATA */
    int init_time;
    int cycles;
    int wait;
    int wait_delay;
    int s;

    /* OUTPUT-DATA */
    int turnos_cpu;
    int interrupciones;
    float turnaround_time;
    float responce_time;
    float waiting_time;

    /* Contadores */
    int count_waiting;
    int count_running;
    int count_cycles;
} Process;

// Declare functions
Process* process_init(char* name, char* pid, char* t_inicio, char* cycles, char* wait, char* wait_delay, char* s);
Process* process_IDLE();
Process** processes_init(InputFile* input_file);