#include <stdio.h>	// FILE, fopen, fclose, etc.
#include <stdlib.h> // malloc, calloc, free, etc
#include "../process/process.h"
#include "../queue/queue.h"
#include "../file_manager/manager.h"


/* Funcion que asigna un Proceso a la CPU dependiendo de la Cola y el Estado del Proceso */
void process_to_cpu(Nodo* cola, Process* CPU)
{
	Nodo* nodo_actual = cola;
	while (nodo_actual != NULL)
	{
		if (nodo_actual->proceso->estado == 0)
		{
			CPU = pop_nodo(cola, nodo_actual);
			CPU->estado = 1;
			break;
		}
		nodo_actual = nodo_actual->next;
	}
}

/* Funcion que cambia del Estado WAITING a READY de un Proceso dependiendo de la Cola y el Estado del Proceso */
void wait_to_ready(Nodo* Cola)
{
	Nodo* nodo_actual = Cola;
	while (nodo_actual != NULL)
	{
		if (nodo_actual->proceso->estado == 2)
		{
			if (nodo_actual->proceso->wait_delay == nodo_actual->proceso->count_waiting)
			{
				nodo_actual->proceso->estado = 0;
			}
		}
		nodo_actual = nodo_actual->next;
	}
}

int write_file(filename)
{
	/* Formato de impresion en el archivo 'output.csv */
	/* 'nombre_proceso,turnos_cpu,interrupciones,turnaround_time,responce_time,waiting_time' */
	return 0;
}

int main(int argc, char const *argv[])
{

	/*Lectura del input*/
	char *file_name = (char *)argv[1];
	InputFile *input_file = read_file(file_name);
	// input_file = {[PROCESO_1], [PROCESO_2], ..., [PROCESO_k]}
	// PROCESO_k = [nombre, PID, t_inicio, Ciclos, wait, wait_delay, S]

	/*Mostramos el archivo de input en consola*/
	printf("Nombre archivo: %s\n", file_name);
	printf("Cantidad de procesos: %d\n", input_file->len);
	printf("Procesos:\n");
	for (int i = 0; i < input_file->len; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			printf("%s ", input_file->lines[i][j]);
		}
		printf("\n");
	}

	/* Instanciacion de los componentes del Scheduler */
	// Process* IDLE = process_IDLE();
	Process* CPU = NULL;


	// proceso de prueba: XD E S T O    E S    D E    P R U E B A
	//instancio un procesp
	Process* proceso_prueba = process_init('NICOLE', '2', '1', '2', '3', '4', '5');
	//instancio cola

	Nodo* Cola = init(NULL, 0); 	// Cola de mayor prioridad tipo FIFO
	append(Cola, proceso_prueba);
	
	// E S T O    E S    D E    P R U E B A ------------------------
	// Instanciacion de las colas
	Nodo* Cola_2 = init(NULL, 0); 	// Cola de mayor prioridad tipo FIFO
	Nodo* Cola_1 = init(NULL, 0);	// Cola de prioridad media tipo FIFO
	Nodo* Cola_0 = init(NULL, 1);	// Cola de menor prioridad tipo SJF

	// Instanciacion de los procesos
	Process** list_process = processes_init(input_file);
	


	/* Inicio del Bucle del Scheduler */
	while (1) // Reemplazar por una codicion mas elaborada
	{
		/* 1.- Actualizar procesos que cumplen su I/O-Burst (WAITING->READY) */
		if (Cola_2->proceso !=NULL)
		{
			wait_to_ready(Cola_2);
		}
		if (Cola_1->proceso !=NULL)
		{
			wait_to_ready(Cola_1);
		}
		if (Cola_0->proceso !=NULL)
		{
			wait_to_ready(Cola_0);
		}
		
		/* 2.- Actualizar el estado del proceso en Running (si corresponde) */
		// Pasa a waiting -> Se completa el atributo 'wait' o se le acaba el q
		// Pasa a Finished -> Se completa el atributo 'cycles'
		if (CPU->count_cycles < CPU->cycles)
		{
			if (CPU->count_running < CPU->q)
			{
				if (CPU->count_waiting == CPU->wait)
				{
					CPU->estado = 2;
				}
			}
			else
			{
				CPU->estado = 0;
			}
		}
		else
		{
			CPU->estado = 3;
		}


		/* 3.- Asignar los procesos a sus respectivas Colas */

		// INGRESO A COLA2 (FIFO)
		////FORMA 1: PROCESO ENTRA POR PRIMERA VEZ A COLA
		for (int i=0; i<input_file->len; i+=1)   //revisar el largo del arreglo D:
			{
				int minimo = list_process[0]->t_inicio; //guardo como minimo el tiempo del primer elemento
				int tiempo_proceso = list_process[i]->t_inicio;
				if (tiempo_proceso < minimo)   //ojo: list_process[i] es un puntero a proceso
				{
					minimo = tiempo_proceso;
				}	
			}
		list_process[i]->estado = 'Ready'; // le actualizo el estado al proceso
		append(Cola_2, list_process); //agrego proceso a cola 
		
		////FORMA 2: SE COMPLETA EL WAIT





		

		/* 4.- Ingresar un proceso a la CPU (READY->RUNNING) */
		
		// revisar Cola_2
		
		if (Cola_2->proceso != NULL && CPU == NULL)
		{
			process_to_cpu(Cola_2, CPU);
		}
		// revisar Cola_1
		if (Cola_1->proceso != NULL && CPU == NULL)
		{
			process_to_cpu(Cola_1, CPU);
		}
		// revisar Cola_0 
		if (Cola_0->proceso != NULL && CPU == NULL)
		{
			process_to_cpu(Cola_0, CPU);
		}

	}

	/*Escritura del output*/
	char *output_name = (char *)argv[2];
	printf("Output_name: %s\n", output_name);

	/* Limpieza de memoria */
	input_file_destroy(input_file);

}

void wait_to_ready(Nodo* Cola)
{
	Nodo* nodo_actual = Cola;
	while (nodo_actual != NULL)
	{
		if (nodo_actual->proceso->estado == 2)
		{
			if (nodo_actual->proceso->wait_delay == nodo_actual->proceso->count_waiting)
			{
				nodo_actual->proceso->estado = 0;
			}
		}
		nodo_actual = nodo_actual->next;
	}
}