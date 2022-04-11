#include <stdio.h>	// FILE, fopen, fclose, etc.
#include <stdlib.h> // malloc, calloc, free, etc
#include <string.h>
#include "../process/process.h"
#include "../queue/queue.h"
#include "../file_manager/manager.h"


/* Funcion que asigna un Proceso a la CPU dependiendo de la Cola y el Estado del Proceso */
Process* process_to_cpu(Nodo* cola, Process* CPU)
{
	Nodo* nodo_actual = cola;
	while (nodo_actual->proceso != NULL)
	{
		printf("El proceso %s entrara en la CPU\n", nodo_actual->proceso->nombre);
		if (nodo_actual->proceso->estado == 0)
		{
			printf("Entro en la CPU\n");
			CPU = pop_nodo(cola, nodo_actual);
			CPU->estado = 1;
			CPU->turnos_cpu += 1;
			CPU->count_running = 0;
			break;
		}
		nodo_actual = nodo_actual->next;
	}
	printf("El proceso %s esta en la CPU\n", CPU->nombre);
	return CPU;
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
			else
			{
				nodo_actual->proceso->count_waiting += 1;
			}
		}
		nodo_actual = nodo_actual->next;
	}
}

void check_envejecimiento(int time, Nodo* cola_inicio, Nodo* cola_final)
{
	Nodo* nodo_actual = cola_inicio;
	while (nodo_actual->proceso != NULL && nodo_actual != NULL)
	{
		printf("Este es el nodo actual: %s\n", nodo_actual->proceso->nombre);
		printf("Su S es el: %d\n", nodo_actual->proceso->s);
		if (((time - nodo_actual->proceso->init_time)%nodo_actual->proceso->s) == 0)
		{
			nodo_actual->proceso->prioridad = 2;
			pop_nodo(cola_inicio, nodo_actual);
			append(cola_final, nodo_actual->proceso);
		}

		nodo_actual = nodo_actual->next;
	}
}

/* Funcion que se encarga de escribir en el archivo de salida "filename" */
void write_file(char* filename, Process* proceso) {
	/* Formato de impresion en el archivo 'output.csv */
	/* 'nombre_proceso,turnos_cpu,interrupciones,turnaround_time,responce_time,waiting_time' */
	char* data_str = compile_data(proceso);

	FILE* output_file = fopen(filename, "a");
    if (!output_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fwrite(data_str, 1, strlen(data_str), output_file);

    fclose(output_file);
}



int main(int argc, char const *argv[])
{

	int input_q = atoi(argv[3]);
	// EXISTE???

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

	// Instanciacion de los componentes del Scheduler 
	// Process* IDLE = process_init("IDLE", "-1", "0", "0", "0", "0", "0");
	Process* CPU = NULL;
	int tiempo = 0;

	// Instanciacion de las colas
	Nodo* Cola_2 = init(NULL, 0); 	// Cola de mayor prioridad tipo FIFO
	Nodo* Cola_1 = init(NULL, 0);	// Cola de prioridad media tipo FIFO
	Nodo* Cola_0 = init(NULL, 1);	// Cola de menor prioridad tipo SJF

	// Instanciacion de los procesos
	Process** list_process = processes_init(input_file);
	
	int contador_procesos = 0;
	// Inicio del Bucle del Scheduler
	while (
		Cola_2->proceso != NULL ||
		Cola_1->proceso != NULL ||
		Cola_0->proceso != NULL ||
		CPU != NULL ||
		contador_procesos <= input_file->len
		)
	{
		/* 1.- Actualizar procesos que cumplen su I/O-Burst (WAITING->READY) */
		if (Cola_2->proceso != NULL)
		{
			wait_to_ready(Cola_2);
		}
		if (Cola_1->proceso != NULL)
		{
			wait_to_ready(Cola_1);
		}
		if (Cola_0->proceso != NULL)
		{
			wait_to_ready(Cola_0);
		}
		
		/* 2.- Actualizar el estado del proceso en Running (si corresponde) (sacar procesos de CPU) */
		if (CPU != NULL)
		{
			if (CPU->count_cycles < CPU->cycles)
			{
				CPU->count_cycles += 1;
				if (CPU->count_running < CPU->quantum)
				{
					CPU->count_running += 1;
					if (CPU->count_waiting == CPU->wait)
					{
						/* Cuando un proceso cede el control de la CPU, aumenta su prioridad */
						CPU->estado = 2;
						CPU->count_waiting = 0;
						if (CPU->prioridad < 2) 
						{
							CPU->prioridad += 1;
						}
					}
				}
				else
				{
					/* Cuando un proceso usa todo su quantum en una detreminada Cola, se reduce su prioridad */
					CPU->estado = 0;
					CPU->interrupciones += 1;
					if (CPU->prioridad > 0)
					{
						CPU->prioridad -= 1;
					}
					//aumentar el contador "Interrupciones"
				}
			}
			else
			{
				CPU->estado = 3;
				// Calculcar TurnAround
			}
		}
		/* 3.- Asignar los procesos a sus respectivas Colas */
		/* 3.1- Si un proceso salio de la CPU, ingresarlo a la cola correspondiente */
		if (CPU != NULL)
		{
			if (CPU->estado == 0)
			{
				if (CPU->prioridad == 2)
				{
					append(Cola_2, CPU);
				}
				else if (CPU->prioridad == 1)
				{
					append(Cola_1, CPU);
				}
				else
				{
					append(Cola_0, CPU);
				}
				CPU = NULL;
			}

			else if (CPU->estado == 2)
			{
				if (CPU->prioridad == 2)
				{
					append(Cola_2, CPU);
				}
				else if (CPU->prioridad == 1)
				{
					append(Cola_1, CPU);
				}
				CPU = NULL;
			}

			else if (CPU->estado == 3)
			{
				// Escribir la DATA del proceso en el archivo
				CPU = NULL;
			}
		}
		
		/* 3.2- Por cada proceso P comprobar si t=t_inicioP e ingresarlo a la primera cola */
		for (int i = 0; i < input_file->len; i++)
		{
			if (list_process[i]->init_time == tiempo) 
			{
				list_process[i]->prioridad = 2;
				list_process[i]->quantum = list_process[i]->prioridad * input_q;
				append(Cola_2, list_process[i]);
				contador_procesos += 1;
			}
		}

		/* 3.3- Por cada proceso P en la segunda cola verificar si [(t - t_inicio)%S_P = 0] e ingresarlo a la primera cola */
		check_envejecimiento(tiempo, Cola_1, Cola_2);
		
		/* 3.4- Por cada proceso P en la tercera cola verificar si [(t - t_inicio)%S_P = 0] e ingresarlo a la primera cola */
		check_envejecimiento(tiempo, Cola_0, Cola_2);

		/* [3.5-] Revisar envejecimiento del proceso en la CPU  */


		/* 4.- Ingresar un proceso a la CPU (READY->RUNNING) */
			/* El quantum se reinicia cada vez que se ingresa a la CPU */
		// revisar Cola_2
		if (Cola_2->proceso != NULL && CPU == NULL)
		{
			CPU = process_to_cpu(Cola_2, CPU);
			// aumentar el contador "turnos_cpu"
			printf("El proceso %s sigue dentro de la CPU luego de la funcion\n", CPU->nombre); // ERROR?!?!?!
		}

		// revisar Cola_1
		if (Cola_1->proceso != NULL && CPU == NULL)
		{
			CPU = process_to_cpu(Cola_1, CPU);
			// aumentar el contador "turnos_cpu"
		}

		// revisar Cola_0 
		if (Cola_0->proceso != NULL && CPU == NULL)
		{
			CPU = process_to_cpu(Cola_0, CPU);
			// aumentar el contador "turnos_cpu"
		}
		// printf("El proceso %s sigue dentro de la CPU luego de la funcion\n", CPU->nombre);

		printf("Este es el final del while en el tiempo t=%d\n", tiempo);
		tiempo += 1;

	}

	/*Escritura del output*/
	char *output_name = (char *)argv[2];
	printf("Output_name: %s\n", output_name);

	/* Limpieza de memoria */
	input_file_destroy(input_file);

}