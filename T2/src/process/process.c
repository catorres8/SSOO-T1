#include "process.h"

struct Process
{
    int PID;
    char nombre[32];
    int prioridad;
    int estado; /* 0=READY; 1=RUNNING; 2=WAITING; 3=FINISHED */
};
