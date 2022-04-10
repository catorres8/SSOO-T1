// Tells the compiler to compile this file once
#pragma once
#include "../process/process.h"


// Define compile-time constants


// Define the struct
typedef struct nodo
{
    int tipo_cola; // 0 = FIFO; 1 = SJF

    //Process* proceso; 
    Process* proceso; // cada elemento de la cola tiene un proceso // VEEEEEEEEEEEEEEEERR!!!!
    struct nodo* next; // cada proceso tiene un siguiente proceso
    
} Nodo; 


// Declare functions
Nodo* init(Process* proceso, int tipo);
void append(Nodo* nodo, Process* proceso);
Nodo* insertar_ordenado(Nodo* inicio, Nodo* nuevo);
Process* pop_head(Nodo* cola);