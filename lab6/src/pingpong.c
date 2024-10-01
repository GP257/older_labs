/*******************************************************************************
 FILE : pingpong.c
 
 LAST MODIFIED : $Date: 2006/02/24 21:56:11 $

 REVISION : $Revision: 1.1 $
 
 DESCRIPTION : MPI ping-pong program, illustrating sending and receiving of
   mesages between two processors. 

 COPYRIGHT :

   The copyright in this unpublished software is the property of 
   Stanford University.

 AUTHORS : John Martin Bodley
           Stanford Center for Computational Earth and Environmental Science
           Stanford University
           Stanford, CA 94305      

==============================================================================*/  
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
/*******************************************************************************
 FUNCTION : main
  
 LAST MODIFIED : Feb 24, 2006
 
 DESCRIPTION : MPI send and receive of data between two processors.
 
==============================================================================*/
  
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int inmsg, outmsg, namelen, numprocs, rank, dest, source, size, tag = 1;
  double startwtime, endwtime, time;
  
  MPI_Status status;

  /* MPI initialization */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);

  printf("Process %d on %s out of %d\n", rank, processor_name, numprocs);

  if (rank == 0) { 
    dest = source = 1; 
    outmsg = 17;
  }
  else if (rank == 1) { 
    dest = source = 0; 
    outmsg = 19;
  }

  /* Start MPI timing */
  if (rank == 0) startwtime = MPI_Wtime();

  if (rank == 0) {
  
    MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
  
  } else if (rank == 1) {
  
    MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
    MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
  }

  /* Elasped time */
  if (rank == 0) {
    endwtime = MPI_Wtime();
    time = 1.0e+6 * (endwtime - startwtime);
    size = sizeof(int);
    
    printf("%8d bytes took %9.0f usec (%8.3f MB/sec)\n", size, time, 
        2.0 * size / time);
  }

  MPI_Finalize();

} /* main */
