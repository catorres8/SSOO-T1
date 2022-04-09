// Tells the compiler to compile this file once
#pragma once
#include "../process/process.h"


// Define compile-time constants


// Define the struct
typedef struct queue
{
    int queue_type; // 0 = FIFO; 1 = SJF

    Process proceso; // cada elemento de la cola tiene un proceso
    struct queue* next; // cada proceso tiene un siguiente proceso
    
} Queue; 


// Declare functions
Queue* init(Process* proceso, int tipo);
void append(Queue* cola, Process* proceso);
Queue* insertar_ordenado(Queue* inicio, Queue* nuevo);