#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include "../process/process.h"

// OBJETIVO:
// Es necesario crear 3 Queue
// La cola numero 2 es la de mayor prioridad; Funciona con esquema FIFO.
// La cola numero 1 es la de prioridad intermedia; Funciona con esquema FIFO.
// La cola numero 0 es la de menor prioridad; Funciona con esquema SJF

Queue* init(Process* proceso, int tipo)
{
    Queue* cola = malloc(sizeof(Queue));
    *cola = (Queue) {
        .queue_type = tipo,
        .proceso = proceso,
        .next = NULL,
    };
    return cola;
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

void append(Queue* cola, Process* proceso) {
    if (cola->queue_type == 0) // Aqui hacemos mecanica FIFO
    {
        // vamos al final de la cola
        Queue *ultimo = cola;
        while (ultimo->next) {
            ultimo = ultimo->next;
        }

        // creamos el nuevo nodo
        Queue *new_list = init(proceso, tipo);

        // Lo agregamos como el nodo siguiente al ultimo nodo de la lista
        ultimo->next = new_list;
    }
    else                       // Aqui hacemos mecanica SJF
    {
        inicio = insertar_ordenado(inicio, proceso); //este inicio tiene que inicializarse en main como   Queue*inicio=nullptr (indica que aun no se apunta a nada, entonces lista es vacia)
    } 
}


// Funcion que se encarga de insertar, ordenadamente (por quantum), los procesos a la cola SFj
/* Dado el puntero inicial a una lista y el puntero a un nuevo nodo que aún no está en la lista, inserta este nuevo nodo en orden ascendente. Retorna el puntero inicial. */
Queue* insertar_ordenado(Queue* inicio, Queue* nuevo) { //ese inicio en el main se definira al principio e ira moviendose. Y ese nuevo es "la cola chica" que quiero ingresar

    // si lista está vacía
    if (inicio == nullptr) {
        inicio = nuevo;
    }

    // si el elemento es el menor
    if (nuevo->proceso.q < inicio->proceso.q) {
    nuevo->next = inicio;
    inicio = nuevo;
    }

    // CASO EN QUE ELEMENTO ES MAYOR A TODOS O INTERMEDIO: 
    //para esto buscamos posicion usando una variable auxiliar (que es puntero a Queue), que contrendra la direccion de memoria
    //del 1ª nodo de de la lista.
    else {
        //Guardamos el inicio de la lista
        Queue* aux = inicio;
        //nos movemos por los elementos de la lista
        while (aux->next != nullptr && aux->next->proceso.q  <  nuevo->proceso.q) {
            aux = aux->next;
        }
        // Si llegamos al final de la lista (o sea el elemento.q es el mayor):
        if (aux->next == nullptr) {
            aux->next = nuevo
        }
        // si el elemento es intermedio
        if (aux->next->proceso.q > nuevo.proceso.q) {
            nuevo->next = aux->next;
            aux->next = nuevo;
        }

    }
    return inicio;
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