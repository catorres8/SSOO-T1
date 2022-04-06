// Tells the compiler to compile this file once
#pragma once

// Define compile-time constants


// Define the struct
typedef struct process
{
    int PID;
    char nombre[32];
    int prioridad;
    int estado; //0=READY; 1=RUNNING; 2=WAITING; 3=FINISHED
    
    /* INPUT-DATA */
    int init_time;
    int cycles;
    int wait;
    int wait_delay;
    int S;

    /* OUTPUT-DATA */
    int turnos_cpu;
    int interrupciones;
    float turnaround_time;
    float responce_time;
    float waiting_time;
} Process;

// Declare functions
