// Tells the compiler to compile this file once
#pragma once

// Define compile-time constants

// Define the struct
typedef struct queue
{
    int queue_type; // 0 = FIFO; 1 = SJF
    int quantum;
    struct queue* next;
    
} Queue;

// Declare functions
Queue* init(int tipo){

    Queue* cola = malloc(sizeof(Queue));

    *cola = (Queue) {
        .queue_type = tipo,
        .processes = malloc(),
        .next = NULL,
    }
    
    return cola
}

void append(Queue* cola, process* proceso) {
    if (cola->queue_type == 0)
    {
        /* code */
    }
    else
    {
        /* code */
    }
    
}

