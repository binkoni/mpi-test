#include <mpi.h>
#include <stdio.h>

#define DIM_SIZE 2

int main(int argc, char** argv) {
    int comm_size;
    int rank;
    int dims[DIM_SIZE] = {3, 2};
    int periods[2] = {1, 0};
    int reorder = 1;
    char comm_name[MPI_MAX_OBJECT_NAME];
    int comm_name_len;

    MPI_Comm comm;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_get_name(MPI_COMM_WORLD, comm_name, &comm_name_len);
    printf("BEFORE.. COMM: %s COMM_SIZE: %d, RANK: %d\n", comm_name, comm_size, rank);

    MPI_Cart_create(MPI_COMM_WORLD, DIM_SIZE, dims, periods, reorder, &comm);

    MPI_Comm_size(comm, &comm_size);
    MPI_Comm_rank(comm, &rank);

    MPI_Comm_get_name(comm, comm_name, &comm_name_len);
    printf("AFTER.. COMM: %s, COMM_SIZE: %d, RANK: %d\n", comm_name, comm_size, rank);

    MPI_Finalize();
    return 0;
}
