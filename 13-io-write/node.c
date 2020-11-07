#include <mpi.h>
#include <stdio.h>

#define BUF_SIZE 100

int main(int argc, char** argv) {
    int rank, comm_size;
    int buf[BUF_SIZE];
    MPI_File file;
    MPI_Offset disp;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (int i = 0; i < BUF_SIZE; ++i)
        buf[i] = rank * BUF_SIZE + i;
    MPI_File_open(MPI_COMM_WORLD, "testfile", MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &file);
    disp = rank * BUF_SIZE * sizeof(int);
    MPI_File_set_view(file, disp, MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
    MPI_File_write(file, buf, BUF_SIZE, MPI_INT, MPI_STATUS_IGNORE);
    MPI_File_close(&file);
    MPI_Finalize();
    return 0;
}
