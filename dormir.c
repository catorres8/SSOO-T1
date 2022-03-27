#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void dormir(int tiempo)
{
    printf("Me voy a mimir\n");
    sleep(tiempo);
    printf("Me desperte\n");
}


int main(int argc, char const *argv[])
{
    int tiempo = atoi(argv[0]);
    dormir(tiempo);
    return 0;
}
