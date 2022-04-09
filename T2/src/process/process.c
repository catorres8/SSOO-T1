#include "process.h"


Process* process_init ()
{
    Process* proceso = malloc(sizeof(Process));
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
        .S = 0,
        .turnos_cpu = 0,
        .interrupciones = 0,
        .turnaround_time = 0,
        .responce_time = 0,
        .waiting_time = 0,
    };
    
    return proceso;
}

