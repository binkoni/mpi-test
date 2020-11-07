#include <mpi.h>
#include <stdio.h>

#define SENDER 0
#define BUF_SIZE 20

int main(int argc, char** argv) {
    int rank, comm_size;
    int buf[BUF_SIZE];
    MPI_Datatype my_type;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == SENDER) {
        for (int i = 0; i < BUF_SIZE ; ++i)
            buf[i] = (i + 1) * 100;
    } else {
        for(int i = 0 ; i < BUF_SIZE; ++i)
            buf[i] = 0;
    }
    MPI_Type_vector(4, 2, 3, MPI_INTEGER, &my_type);
    MPI_Type_commit(&my_type);
    MPI_Bcast(buf, 1, my_type, SENDER, MPI_COMM_WORLD);
    printf("rank: %d buf: ", rank);
    for (int i = 0; i < BUF_SIZE; ++i)
        printf(" %d", buf[i]);
    printf("\n");
    MPI_Finalize();
    return 0;
}
