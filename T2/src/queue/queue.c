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

Nodo* append(Nodo* cabeza, Process* proceso)

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
    return cabeza;
}


// Funcion que se encarga de insertar, ordenadamente (por quantum), los procesos a la cola SFJ
/* Dado el puntero inicial a una lista y el puntero a un nuevo nodo que aún no está en la lista, inserta este nuevo nodo en orden ascendente. Retorna el puntero inicial. */
Nodo* insertar_ordenado(Nodo* inicio, Nodo* nuevo) { //ese inicio en el main se definira al principio e ira moviendose. Y ese nuevo es "la cola chica" que quiero ingresar

    // si lista está vacía
    if (inicio == NULL) {
        inicio = nuevo;
    }

    // si el elemento es el menor
    if (nuevo->proceso->quantum < inicio->proceso->quantum) {
    nuevo->next = inicio;
    inicio = nuevo;
    printf("{insertar} Nombre del proceso inicio %s\n", inicio->proceso->nombre);
    return inicio;
    }
    // CASO EN QUE ELEMENTO ES MAYOR A TODOS O INTERMEDIO: 
    //para esto buscamos posicion usando una variable auxiliar (que es puntero a Queue), que contrendra la direccion de memoria
    //del 1ª nodo de de la lista.
    else {
        //Guardamos el inicio de la lista
        Nodo* aux = inicio;
        //nos movemos por los elementos de la lista
        while (aux->next != NULL && aux->next->proceso->quantum  <  nuevo->proceso->quantum) {
            aux = aux->next;
            
        }
        // Si llegamos al final de la lista (o sea el elemento.q es el mayor):
        if (aux->next == NULL) {
            aux->next = nuevo;
        }
        // si el elemento es intermedio
        if (aux->next->proceso->quantum > nuevo->proceso->quantum) {
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

Nodo* pop_nodo(Nodo *cabeza, Nodo* objetivo)
{
    Nodo* nodo_anterior = NULL;
    Nodo* nodo_actual = cabeza;
    while (nodo_actual!=objetivo)
    {
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->next;
    }
    if (nodo_anterior == NULL) // Primer elemento (Cabeza)
    {
        if (nodo_actual->next == NULL)
        {
            cabeza->proceso = NULL;
        }
        else
        {
            cabeza = nodo_actual->next; // .next = Null
            cabeza->proceso = nodo_actual->next->proceso;
        }
        return cabeza;
    }
    else // Otro elemento
    {
        nodo_anterior->next = nodo_actual->next;
        //free(nodo_actual);
        return cabeza;
    }
}