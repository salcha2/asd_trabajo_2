#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define ITERATIONS 1000000

int main(int argc, char *argv[]) {
    int rank, size;
    int i, count = 0, total_count = 0;
    double x, y, z, pi;
    double start_time, end_time, elapsed_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);

    start_time = MPI_Wtime(); // Start measuring time

    for (i = 0; i < ITERATIONS / size; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        z = x * x + y * y;
        if (z <= 1) count++;
    }

    MPI_Barrier(MPI_COMM_WORLD); // Synchronize all processes before reducing count

    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi = ((double) total_count / ITERATIONS) * 4;
        printf("Estimación de PI: %f\n", pi);
    }

    end_time = MPI_Wtime(); // End measuring time
    elapsed_time = end_time - start_time;

    double max_time;
    MPI_Reduce(&elapsed_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Tiempo total: %f segundos\n", max_time);
    }

    MPI_Finalize();

    return 0;
}
