#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, comm_size;
    int buf[10];
    MPI_Aint address1, address2;
    MPI_Init(&argc, &argv);

    MPI_Get_address(&buf[0], &address1);
    MPI_Get_address(&buf[4], &address2);
    printf("length(byte) of a[4] - a[0] : %d\n", (int) (address2 - address1));

    MPI_Finalize();
    return 0;
}
