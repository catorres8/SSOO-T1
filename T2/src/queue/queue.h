// Tells the compiler to compile this file once
#pragma once
#include <stdlib.h>
#include <stdio.h>
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
Queue* init(Process* proceso, int tipo)
{
    Queue* cola = malloc(sizeof(Queue));
    *cola = (Queue) {
        .queue_type = tipo,
        .proceso = proceso,
        .next = NULL,
    }
    return cola
}


void append(Queue* cola, Process* proceso) {
    if (cola->queue_type == 0) // Aqui hacemos mecanica FIFO
    {
        // vamos al final de la cola
        Queue *ultimo = cola;
        while (ultimo->next) {
            ultimo = ultimo->next;
        }

        // creamos el nuevo nodo
        Queue *new_list = init(proceso, cola->queue_type);

        // Lo agregamos como el nodo siguiente al ultimo nodo de la lista
        ultimo->next = new_list;
    }
    else                       // Aqui hacemos mecanica SJF
    {
        /* code 
        - recorro cola, 
        - y comparo mi proceso.quantum, con cada proceso,quantum de la cola 
            - si mi proceso.quantum < a cada proceso.quantum de la cola:
                - 
        - luego la recorro, la menor, y agrego a otra lista ligada (en donde estaran ordenado por SFJ)
        mmmm ta raro
        */
    }
    
}


// CODIGO ANTERIOR

// typedef struct queue
// {
//     int queue_type; // 0 = FIFO; 1 = SJF
//     int priority;
//     int quantum;
//     struct queue* previous; // Rerferencia al elemento anterior
//     struct queue* next;    // Referencia al elemento siguiente
// } Queue;


// Queue* init(int tipo, int prioridad, int input_q){
//     Queue* cola = malloc(sizeof(Queue));
//     *cola = (Queue) {
//         .queue_type = tipo,
//         .priority = prioridad,
//         .quantum = prioridad * input_q,
//         .processes = malloc(Process),
//         .previous = NULL,
//         .next = NULL,
//     }
//     return cola
// }


// void append(Queue* cola, process* proceso) {
//     if (cola->queue_type == 0)
//     {
//         /* code */
//     }
//     else
//     {
//         /* code */
//     }
// }