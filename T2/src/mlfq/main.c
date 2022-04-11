#include <stdio.h>	// FILE, fopen, fclose, etc.
#include <stdlib.h> // malloc, calloc, free, etc
#include <string.h>
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
			CPU->turnos_cpu += 1;
			CPU->count_running = 0;
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
			else
			{
				nodo_actual->proceso->count_waiting += 1;
			}
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
	Process* IDLE = process_init("IDLE", "-1", "0", "0", "0", "0", "0");
	Process* CPU = IDLE;
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
		
		/* 2.- Actualizar el estado del proceso en Running (si corresponde) (sacar procesos de CPU) */
		// Pasa a waiting -> Se completa el atributo 'wait' o se le acaba el q
		// Pasa a Finished -> Se completa el atributo 'cycles'
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


		/* ------------------ INGRESO A COLA 1 (FIFO) ----------------------------------- */
		//  (bajó de prioridad de 2-->1)  o (proceso cedio la cpu en la cola de abajo ^ prioridad es 1 )
		if (CPU != NULL)
		{
			if ((CPU->prioridad==1 && CPU->estado==0) || (CPU->estado==2 && CPU->prioridad==1))
			{
				Process* proceso_a_agregar = CPU;
				proceso_a_agregar->quantum = proceso_a_agregar->prioridad * input_q;
				append(Cola_1, proceso_a_agregar); //agrego proceso a cola
			}

			/* ------------------ INGRESO A COLA 0 (SLF) ----------------------------------- */
			//  (bajó de prioridad de 1-->0)  
			else if (CPU->prioridad==0 && CPU->estado==0)
			{
				Process* proceso_a_agregar = CPU;
				append(Cola_0, proceso_a_agregar); //agrego proceso a cola
			}
		

		/* ------------------ INGRESO A COLA 2 (FIFO: MENOR T_INICIO) ------------------ */
		//recorro lista de procesos
		int minimo2 = list_process[0]->init_time; //guardo como minimo el tiempo del primer elemento
		Process* proceso_a_agregar = list_process[0]; // puntero proceso 0
		
			for (int j=0; j<input_file->len; j+=1)
			{
				for (int i=0; i<input_file->len; i+=1)   //revisar el largo del arreglo D:
				{
						int tiempo_proceso = list_process[i]->init_time; // tiempo del proceso i

					// si proceso entra por primera vez, o (viene desde la cpu porque ya completo su wait o cedio la cpu en la cola de abajo ^ prioridad sigue siendo/es 2)
					if ((list_process[i]->estado==0) || (CPU->estado==2 && CPU->prioridad==2))
					{
						//revisamos si proceso estra por primera vez, para sumarle al contador
						if (list_process[i]->estado==0)
						{
							contador_procesos +=1;
						}
								
						if (tiempo_proceso < minimo2)   // obtengo proceso de t_inicio menor
						{
							minimo2 = tiempo_proceso; // actualizo el minimo
							proceso_a_agregar =  list_process[i]; // actualizo proceso_a_agregar
						}
					}

				}
				if (proceso_a_agregar->init_time == tiempo)
				{
					proceso_a_agregar->quantum = proceso_a_agregar->prioridad * input_q;
					append(Cola_2, proceso_a_agregar); //agrego proceso a cola 

					printf("Este es el proceso:%s\n",proceso_a_agregar->nombre);
					printf("Esta esel proceso desde la cola :%s\n",Cola_2->proceso->nombre);
				}

			}
			
		/* ------------------ INGRESO A COLA 2 desde Cola_1 (Por envejecimiento) ------------------ */

			Nodo* cabeza1 = Cola_1;
			// vamos al final de la cola
			while (cabeza1->next) {
				if (cabeza1->proceso->s == cabeza1->proceso->count_s)
				{
					Process* proceso_append = pop_nodo(Cola_1, cabeza1);
					proceso_a_agregar->quantum = proceso_a_agregar->prioridad * input_q;
					append(Cola_2, proceso_append);
				}
				else
				{
					cabeza1->proceso->count_s += 1;
				}
				cabeza1 = cabeza1->next;
			}
		
		/* ------------------ INGRESO A COLA 2 desde Cola_0 (Por envejecimiento) ------------------ */		

			Nodo* cabeza0 = Cola_0;
			while(cabeza0->next)
			{
				if (cabeza0->proceso->s == cabeza0->proceso->count_s)
				{
					Process* proceso_append = pop_nodo(Cola_0, cabeza0);
					proceso_a_agregar->quantum = proceso_a_agregar->prioridad * input_q;
					append(Cola_2, proceso_append);
				}
				else
				{
					cabeza0->proceso->count_s += 1;
				}
				cabeza0 = cabeza0->next;
			}
		}

		/* 4.- Ingresar un proceso a la CPU (READY->RUNNING) */
			/* El quantum se reinicia cada vez que se ingresa a la CPU */
		// revisar Cola_2
		if (Cola_2->proceso != NULL && CPU == NULL)
		{
			process_to_cpu(Cola_2, CPU);
			// aumentar el contador "turnos_cpu"
		}

		// revisar Cola_1
		if (Cola_1->proceso != NULL && CPU == NULL)
		{
			process_to_cpu(Cola_1, CPU);
			// aumentar el contador "turnos_cpu"
		}

		// revisar Cola_0 
		if (Cola_0->proceso != NULL && CPU == NULL)
		{
			process_to_cpu(Cola_0, CPU);
			// aumentar el contador "turnos_cpu"
		}

		// printf("Este es el final del while en el tiempo t=%d\n", tiempo);
		tiempo += 1;

	}

	/*Escritura del output*/
	char *output_name = (char *)argv[2];
	printf("Output_name: %s\n", output_name);

	/* Limpieza de memoria */
	input_file_destroy(input_file);

}



