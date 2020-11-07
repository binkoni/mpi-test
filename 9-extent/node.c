#include <mpi.h>
#include <stdio.h>

#define SENDER 0
#define RECEIVER 1
#define TAG 52

int main(int argc, char** argv) {
    int rank, comm_size;
    MPI_Status status;
    struct {
        int i;
        float f;
        double d[4];
    } my_struct;
    int block_lengths[3] = {1, 1, 4};
    MPI_Datatype item_types[3] = {MPI_INT, MPI_FLOAT, MPI_DOUBLE};
    MPI_Aint displacements[3];
    MPI_Datatype my_type;
    MPI_Aint int_lb, float_lb;
    MPI_Aint int_extent, float_extent;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    MPI_Type_get_extent(MPI_INT, &int_lb, &int_extent);
    MPI_Type_get_extent(MPI_FLOAT, &float_lb, &float_extent);
    displacements[0] = (MPI_Aint)0;
    displacements[1] = int_extent;
    displacements[2] = int_extent + float_extent;
    MPI_Type_create_struct(3, block_lengths, displacements, item_types, &my_type);
    MPI_Type_commit(&my_type);
    if (rank == SENDER) {
        my_struct.i = 6;
        my_struct.f = 3.14;
        for (int i = 0; i < 4; ++i)
            my_struct.d[i] = i;
        MPI_Send(&my_struct, 1, my_type, RECEIVER, TAG, MPI_COMM_WORLD);
    } else if (rank == RECEIVER) {
        MPI_Recv(&my_struct, 1, my_type, SENDER, TAG, MPI_COMM_WORLD, &status);
        printf("rank: %d, my_struct: %d %f %lf %lf %lf %lf\n", rank, my_struct.i, my_struct.f, my_struct.d[0], my_struct.d[1], my_struct.d[2], my_struct.d[3]);
    }

    MPI_Finalize();
    return 0;
}
