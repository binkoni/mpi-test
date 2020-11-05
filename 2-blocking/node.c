#include <stdio.h>
#include <mpi.h>

#define SEND_SIZE 100
#define RECV_SIZE 200

int main(int argc, char *argv[]) {
    int rank, i, count;
    float data[SEND_SIZE], value[RECV_SIZE];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 1) {
        for (i = 0; i < SEND_SIZE; ++i)
            data[i] = i;
        MPI_Send(data, SEND_SIZE, MPI_FLOAT, 0, 55, MPI_COMM_WORLD);
    } else {
        MPI_Recv(value, RECV_SIZE, MPI_FLOAT, MPI_ANY_SOURCE, 55, MPI_COMM_WORLD, &status);
        printf("P: %d Got data from processor %d\n", rank, status.MPI_SOURCE);
        MPI_Get_count(&status, MPI_FLOAT, &count);
        printf("P: %d Got %d elements \n", rank, count);
        for (i = 0; i < RECV_SIZE; ++i) {
            printf("P: %d value[%d] = %f\n", rank, i, value[i]);
        }
    }
    MPI_Finalize();
}
