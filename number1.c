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

    // we only want 5 processes for this program
    // this is part of the ring structure requirement
    // if it's not 5, we stop early and print an error
    // only rank 0 prints to avoid duplicate messages
    if (size != 5) {
        if (rank == 0) {
            printf("error: must run with exactly 5 processes\n");
        }
        MPI_Finalize();
        return 1;
    }

    // we expect 5 numbers to be passed in through the command line
    // argc includes the program name, so total should be 6 (program + 5 numbers)
    // if not, we show a usage message and exit the program early
    // only rank 0 prints the message to avoid clutter
    if (argc != 6) {
        if (rank == 0) {
            printf("usage: ./numbers1 <5 numbers>\n");
        }
        MPI_Finalize();
        return 1;
    }

    // each process reads one number from argv based on its rank
    // rank 0 reads argv[1], rank 1 reads argv[2], etc.
    // atoi converts the string input to an actual integer
    int my_number = atoi(argv[rank + 1]);
    printf("process %d got number %d\n", rank, my_number);

    // calculate neighbor ranks in the ring
    // wrap-around is handled by using modulo math
    int left = (rank - 1 + size) % size;
    int right = (rank + 1) % size;

    // show neighbor relationships for debugging
    printf("process %d has left neighbor %d and right neighbor %d\n", rank, left, right);
    MPI_Finalize();
    return 0;
}
