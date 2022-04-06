#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    float num_1 = atof(argv[1]);
    float num_2 = atof(argv[2]);

    float average = (num_1 + num_2) / 2;

    printf("El promedio entre %f y %f es %f\n", num_1, num_2, average);

    return 0;
}
