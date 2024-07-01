#include <stdio.h>
#include <string.h>
#include <mpi.h>
const int MAX_SIZE = 100;

int main()
{
    int comm_size, rank; // comm_size = number of processes, rank = process's rank
    char message[MAX_SIZE];
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank !=0)
    {
        printf("Sending message from process %d\n", rank);
        sprintf(message, "Hello from process %d of %d\n", rank, comm_size);
        MPI_Send(message, strlen(message)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        printf("Hello, this is receiver process with rank: %d of %d\n", rank, comm_size);
        printf("Starting to receive...\n");
        for(int i = 1; i < comm_size; i++)
        {
            printf("Receiving begins \n");
            MPI_Recv(message, MAX_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
            printf("%s\n", message);
        }
    }

    MPI_Finalize();
    return 0;
}