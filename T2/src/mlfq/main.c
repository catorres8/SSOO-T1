#include <stdio.h>	// FILE, fopen, fclose, etc.
#include <stdlib.h> // malloc, calloc, free, etc
#include "../process/process.h"
#include "../queue/queue.h"
#include "../file_manager/manager.h"


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
	// input_file = [[PROCESO_1], [PROCESO_2], ..., [PROCESO_k]]
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
	Process* IDLE = process_IDLE();
	Process* CPU = NULL;

	// Instanciacion de las colas
	Queue* Cola_2 = init(IDLE, 0);
	Queue* Cola_1 = init(IDLE, 0);
	Queue* Cola_0 = init(IDLE, 1);

	// Instanciacion de los procesos



	/* Inicio del Bucle del Scheduler */
	while (1) // Reemplazar por una codicion mas elaborada
	{
		/* 1.- Actualizar procesos qie cumplen su I/O-Burst (WAITING->READY) */
		

		/* 2.- Actualizar el estado del proceso en Running (si corresponde) */


		/* 3.- Asignar los procesos a sus respectivas Colas */


		/* 4.- Ingresar un proceso a la CPU (READY->RUNNING) */
	}
	


	/*Escritura del output*/
	char *output_name = (char *)argv[2];
	printf("Output_name: %s\n", output_name);

	input_file_destroy(input_file);
}

/*
typedef struct outputfile {
  int len;
  char*** lines;  // This is an array of arrays of strings
} OutputFile;

OutputFile* write_file(char* filename)
{
*/