#include <mpi.h>
#include <stdio.h>

#define RECEIVER 0

int main(int argc, char** argv) {
    int rank, comm_size;
    int isend;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    int irecv[comm_size];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    isend = rank + 1;
    // if send more data than receive buffer, buffer overflow occurs, so use comm_size
    MPI_Gather(&isend, 1, MPI_INTEGER, irecv, 1, MPI_INTEGER, RECEIVER, MPI_COMM_WORLD);
    if (rank == RECEIVER) {
        printf("irecv = ");
        for (int i = 0; i < comm_size; ++i)
            printf(" %d", irecv[i]);
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}

