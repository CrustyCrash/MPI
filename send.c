#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#define N 10

int main(int argc, char *argv[]) 
{
  int rank, size;
  int* my_val = (int*)malloc(N * sizeof(int));

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    
    for(int i = 0 ; i < N; i++)
    {
        my_val[i] = i;

    }
    MPI_Send(my_val, N, MPI_INT, 1, 0, MPI_COMM_WORLD);

  }
  else if (rank == 1)
  {
    
    MPI_Recv(my_val, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    for(int i = 0; i < N; i ++)
    {
        printf("value after receiving; %d\n", my_val[i]);
    }
  }
  else
  {
    printf("invalid rank\n");
  }

  MPI_Finalize();
  return 0;
}

