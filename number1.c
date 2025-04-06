// Adam Dao
// A1797499

/*
Description:
This MPI program runs 5 processes in a ring topology.
Each process gets a number from command-line input and checks if it's smaller than its left neighbor.
Neighbors are calculated using modular arithmetic to wrap around the ring.
Each process sends its number to the right and receives from the left.
If its number is out of order, it prints a message, then all processes signal when they're done.
Code is structured step-by-step with comments explaining input, neighbors, communication, and logic.
*/



#include <mpi.h>    // for MPI functions
#include <stdio.h>  // for printf

int main(int argc, char** argv) {
    // we start by initializing the MPI environment
    // this must be done before using any MPI functions
    // all processes enter this block together
    // each process will continue from here after MPI is ready
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // gets the process id (0 to size-1)
    MPI_Comm_size(MPI_COMM_WORLD, &size); // gets the total number of processes

    // this is a test to make sure each process knows who it is
    // helps check if mpi was set up right and running as expected
    // we print out the rank and the total size
    // every process should print a unique line
    printf("process %d of %d is running\n", rank, size);

    // once we’re done, we shut down the MPI environment
    // all processes should call this before they exit
    // this frees up the resources used by MPI
    MPI_Finalize();
    return 0;
}
