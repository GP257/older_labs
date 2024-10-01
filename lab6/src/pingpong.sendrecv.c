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

#include "mpi.h"

int main(int argc, char *argv[]) {
/*******************************************************************************
 FUNCTION : main
  
 LAST MODIFIED : Feb 24, 2006
 
 DESCRIPTION : MPI send and receive of data between two processors.
 
==============================================================================*/

  int numprocs, rank, dest, source, tag = 1;
  int i, j, *inmsg, *outmsg, n = 1000, m = 20, p, size;
  double startwtime, endwtime, time;
  int namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);

  printf("Process %d on %s out of %d\n", rank, processor_name, numprocs);

  /* Initialize arrays */
  p = (int) pow(2, m);
  outmsg = (int *) malloc(sizeof(int) * p);
  inmsg = (int *) malloc(sizeof(int) * p);

  if (rank == 0) { 
    dest = source = 1; 
    
    for (i = 0; i < p; i++) {
      outmsg[i] = 17;
    }    
  }
  else if (rank == 1) {
    dest = source = 0; 
    
    for (i = 0; i < p; i++) {
      outmsg[i] = 19;
    }
  } 
  
  for (j = 0; j <= m; j++) {
    p = (int) pow(2.0, (double) j);
  
    if (rank == 0) startwtime = MPI_Wtime();
   
    for (i = 0; i < n; i++) {
      MPI_Sendrecv(outmsg, p, MPI_INT, dest, tag, inmsg, p, MPI_INT, source, 
        tag, MPI_COMM_WORLD, &status);
    }    
      
    if (rank == 0) {  
      endwtime = MPI_Wtime();
      time = 1.0e+6 * (endwtime - startwtime) / (double) n;
      size = p * sizeof(int);
    
      printf("%8d bytes took %9.0f usec (%8.3f MB/sec)\n", size, time, 
        2.0 * size / time);
    }
  }
 
  MPI_Finalize();

} /* main */
