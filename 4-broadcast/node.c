#include <stdio.h>
#include <mpi.h>

#define MSG_SIZE 4
#define ROOT_NODE 0

int main(int argc, char *argv[]) {
    int rank;
    int msg_send[MSG_SIZE];
    int msg_recv[MSG_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == ROOT_NODE) {
        for (int i = 0; i < MSG_SIZE; ++i)
            msg_send[i] = (i + 1) * 100;
        MPI_Bcast(msg_send, MSG_SIZE, MPI_INTEGER, ROOT_NODE, MPI_COMM_WORLD);
    } else {
        MPI_Bcast(msg_recv, MSG_SIZE, MPI_INTEGER, ROOT_NODE, MPI_COMM_WORLD);
        for (int i = 0; i < MSG_SIZE; ++i)
            printf("P: %d msg[%d] = %d\n", rank, i, msg_recv[i]);
    }
    MPI_Finalize();
    return 0;
}
