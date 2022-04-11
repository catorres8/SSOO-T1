#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include "../process/process.h"

// OBJETIVO:
// Es necesario crear 3 Queue
// La cola numero 2 es la de mayor prioridad; Funciona con esquema FIFO.
// La cola numero 1 es la de prioridad intermedia; Funciona con esquema FIFO.
// La cola numero 0 es la de menor prioridad; Funciona con esquema SJF

Nodo* init(Process* proceso, int tipo)
{
    Nodo* cola = malloc(sizeof(Nodo));
    *cola = (Nodo) {
        .tipo_cola = tipo,
        .proceso = proceso,
        .next = NULL,
    };
    return cola;
}

void append(Nodo* cabeza, Process* proceso)

{   //si lista es vacia
    if (cabeza->proceso == NULL)
    {
        cabeza->proceso = proceso;
    }
    // si el nodo es tipo FIFO
    else if (cabeza->tipo_cola == 0) 
    {
        // vamos al final de la cola
        Nodo* ultimo = cabeza;
        while (ultimo->next) {
            ultimo = ultimo->next;
        }
        Nodo* nuevo_nodo = init(proceso, 0);
        ultimo->next = nuevo_nodo;
    }

    // si el nodo es tipo SFJ
    else
    {
        Nodo* nodo_nuevo = init(proceso, 1);
        cabeza = insertar_ordenado(cabeza, nodo_nuevo);
    }
}


// Funcion que se encarga de insertar, ordenadamente (por quantum), los procesos a la cola SFJ
/* Dado el puntero inicial a una lista y el puntero a un nuevo nodo que aún no está en la lista, inserta este nuevo nodo en orden ascendente. Retorna el puntero inicial. */
Nodo* insertar_ordenado(Nodo* inicio, Nodo* nuevo) { //ese inicio en el main se definira al principio e ira moviendose. Y ese nuevo es "la cola chica" que quiero ingresar

    // si lista está vacía
    if (inicio == NULL) {
        inicio = nuevo;
    }

    // si el elemento es el menor
    if (nuevo->proceso->cycles < inicio->proceso->cycles) {
    nuevo->next = inicio;
    inicio = nuevo;
    }

    // CASO EN QUE ELEMENTO ES MAYOR A TODOS O INTERMEDIO: 
    //para esto buscamos posicion usando una variable auxiliar (que es puntero a Queue), que contrendra la direccion de memoria
    //del 1ª nodo de de la lista.
    else {
        //Guardamos el inicio de la lista
        Nodo* aux = inicio;
        //nos movemos por los elementos de la lista
        while (aux->next != NULL && aux->next->proceso->cycles  <  nuevo->proceso->cycles) {
            aux = aux->next;
            
        }
        // Si llegamos al final de la lista (o sea el elemento.q es el mayor):
        if (aux->next == NULL) {
            aux->next = nuevo;
        }
        // si el elemento es intermedio
        if (aux->next->proceso->cycles > nuevo->proceso->cycles) {
            nuevo->next = aux->next;
            aux->next = nuevo;
        }

    }
    return inicio;
}

/* 
Funcion que entrega el Proceso del NodoCabeza de la Cola,
asignando como nuevo NodoCabeza al siguiente Nodo de la Cola 
*/
//REVISAR: ELIMINAR DE MEMORIA AL NODO
Process* pop_head(Nodo* cola)
{
    Process* proceso = cola->proceso;
    if (cola->next != NULL)
    {
        cola = cola->next;
    }
    else
    {
        cola->proceso = NULL;
    }

    return proceso;
}

Process* pop_nodo(Nodo* cabeza, Nodo* objetivo)
{
    if (cabeza == objetivo)
    {
        Process* proceso = cabeza->proceso;
        if (cabeza->next != NULL)
        {
            cabeza = cabeza->next;
            //IMPORTANTE: eliminar cabeza
        }
        else
        {
            cabeza->proceso = NULL;
        }
        return proceso;
    }

    Nodo* nodo_anterior = cabeza;
    Nodo* nodo_actual = cabeza->next;
    while (nodo_actual != objetivo)
    {
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->next;
    }
    Process* proceso = nodo_actual->proceso;
    nodo_anterior->next = nodo_actual->next; // Conecto el nodo_anterior con el sucesor del nodo_actual
    //IMPORTANTE: eliminar nodo_actual

    return proceso;
}