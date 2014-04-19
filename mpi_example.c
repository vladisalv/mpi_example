#include <mpi.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH_MASSIVE 1000000

int main(int argc, char *argv[])
{
    int i;
    int rank, size;
    int root = 0;
    double time, *time_mas, max_time = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    time = MPI_Wtime(); /* Start time */

    if (rank == root)
        printf("Hi, I'm root. You have %d process\n", size);

    /* Share massive to process, and do some action */
    int my_length = LENGTH_MASSIVE / size;
    int *a = (int *)malloc(sizeof(int) * my_length);
    for (i = 0; i < my_length; i++)
        a[i] = i * sin((double)i);

    time = MPI_Wtime() - time;
    time *= 1000; /* For visibility */

    /* Compute max time */
    if (rank == root)
        time_mas = (double *)malloc(sizeof(double) * size);
    MPI_Barrier(MPI_COMM_WORLD);
    /* Send value time from all process to root in time_mas */
    MPI_Gather(&time, 1, MPI_DOUBLE, time_mas, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);
    if (rank == root) {
        for (i = 0; i < size; i++)
            if (time_mas[i] > max_time)
                max_time = time_mas[i];
        printf("Max time = %lf\n", max_time);
    }
    MPI_Finalize();

    return 0;
}
