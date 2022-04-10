#include "process.h"
#include "../file_manager/manager.h"



Process* process_init(char* name, char* pid, char* t_inicio, char* cycles, char* wait, char* wait_delay, char* s)
{
    Process* proceso = malloc(sizeof(Process));
    *proceso = (Process) {
        .PID = atoi(pid),
        .nombre = name,
        .prioridad = 2,
        .estado = 0,
        .q = 0,
        .init_time = atoi(t_inicio),
        .cycles = atoi(cycles),
        .wait = atoi(wait),
        .wait_delay = atoi(wait_delay),
        .s = atoi(s),
        .turnos_cpu = 0,
        .interrupciones = 0,
        .turnaround_time = 0,
        .responce_time = 0,
        .waiting_time = 0,
        .count_waiting = 0,
        .count_running = 0,
        .count_cycles = 0,
    };

    return proceso;
}

Process* process_IDLE (){
    Process* proceso = malloc(sizeof(Process));
    *proceso = (Process) {
        .PID = 0,
        .nombre = "IDLE",
        .prioridad = 0,
        .estado = 0,
        .init_time = 0,
        .cycles = 0,
        .wait = 0,
        .wait_delay = 0,
        .s = 0,
        .turnos_cpu = 0,
        .interrupciones = 0,
        .turnaround_time = 0,
        .responce_time = 0,
        .waiting_time = 0,
        .count_waiting = 0,
        .count_running = 0,
        .count_cycles = 0,
    };
    
    return proceso;
}

/* Funcion que recive una lista con el detalle de inicio de los procesos y los instancia,
retornando una lista con ellos */
Process** processes_init(InputFile* input_file)
{
    Process** list_process[input_file->len];
    for (int i = 0; i < input_file->len; ++i)
    {
        Process* proceso =  process_init(
            input_file->lines[i][0], 
            input_file->lines[i][1], 
            input_file->lines[i][2], 
            input_file->lines[i][3], 
            input_file->lines[i][4], 
            input_file->lines[i][5], 
            input_file->lines[i][6]
        );
        list_process[i] = proceso;
    }

    return list_process;
}
