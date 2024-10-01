/*******************************************************************************
 FILE : advection.c
 
 LAST MODIFIED : $Date: 2006/02/24 21:56:11 $

 REVISION : $Revision: 1.1 $
 
 DESCRIPTION : One-dimensional advection equation.

 COPYRIGHT :

   The copyright in this unpublished software is the property of 
   Stanford University.

 AUTHORS : John Martin Bodley
           Stanford Center for Computational Earth and Environmental Science
           Stanford University
           Stanford, CA 94305      

==============================================================================*/  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "mpi.h"

/*
Variable Type Definitions
-------------------------
*/

typedef struct {
/*******************************************************************************
 STRUCTURE : plot_solution
  
 LAST MODIFIED : Feb 24, 2005
 
 DESCRIPTION : Discretization structure.
 
==============================================================================*/

  double x, t;

} delta_t;

int advection(int m, int n, int numprocs, int rank, double T, double *u, 
  double a) {
/*******************************************************************************
 FUNCTION : advection
  
 LAST MODIFIED : Feb 24, 2006
 
 DESCRIPTION : Solves the one-dimensional advection equation using upwinding
   and explicit Euler discretization.
 
==============================================================================*/

  int  i, s, t, left, right;
  double gamma, mysum, sum, *v, x;
  
  delta_t delta;
  MPI_Status status;
  
  /* Solution at next time step */
  v = (double *) malloc(sizeof(double) * m);

  /* Spatial discretization */
  delta.x = 1.0 / (double) n;

  /* Time step satisfying CFL condition */
  delta.t = delta.x / a;
  gamma = a * delta.t / delta.x;
  
  /* Boundary conditions u(0, t) */
  if (rank == 0) {
    u[1] = 0.0;
  }

  /* Global x coordinates */
  x = (double) ((m - 1) * rank) * delta.x;
 
  for (i = 1; i < m; i++) {
    
    if (x >= 0.0 && x <= 0.2) {
      u[i] = 1 - pow(10.0 * x - 1.0, 2.0); 
    }
    x += delta.x;
  }
  
  left = rank - 1;
  right = rank + 1;
  
  /* Correct source and destination id */
  if (rank == 0) {
    
    /* Don't receive from anyone */
    left = MPI_PROC_NULL;
    
  }
  if (rank == (numprocs - 1)) {
    
    /* Don't send to anyone */
    right = MPI_PROC_NULL;
  }
  
  /* Loop over time (indices) */
  s = (int) (T / delta.t);
  for (t = 0; t < s; t++) {
    
    /* Send information to the right */
    MPI_Send(&u[m - 1], 1, MPI_DOUBLE, right, 0, MPI_COMM_WORLD);
    
    /* Receive infomation from the left u[i - 1] */
    MPI_Recv(&u[0], 1, MPI_DOUBLE, left, 0, MPI_COMM_WORLD, &status);
    
    /* Loop over space */
    for (i = 1; i < m; i++) {
      v[i] = u[i] - gamma * (u[i] - u[i - 1]); 
    }
    
    /* Update solution */
    for (i = 1; i < m; i++) {
      u[i] = v[i]; 
    }
  } 
  
  /* Exact solution */
  for (i = 1; i < m; i++) {
    v[i] = 0.0;
  }
 
  /* Global (x - ut) coordinates */
  x = (double) ((m - 1) * rank) * delta.x - a * T;
 
  for (i = 1; i < m; i++) {
    if (x >= 0.0 && x <= 0.2) {
      v[i] = 1 - pow(10.0 * x - 1.0, 2.0); 
    }
    x += delta.x;
  }
  
  /* L-2 Error norm */
  mysum = 0.0;
  
  for (i = 1; i < m; i++) {
    mysum += pow(v[i] - u[i], 2.0);
  } 
  MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  
  if (rank == 0) {
    printf("residual error for n = %d is: %e\n", n, sqrt(sum));
  }

  free(v);
  
  return(1);
   
} /* advection */

int get_args(int argc, char **argv, int *n, double *T, double *a, char **file) {
/*******************************************************************************
 FUNCTION : get_args
  
 LAST MODIFIED : Feb 24, 2006
 
 DESCRIPTION : Parses command line arguments.
 
==============================================================================*/

  int i;
  
  if (argc <= 1) {
  
    printf("Usage:\n\n"
      "%s [-n <number>] [-T <time>] [-a <velocity>] [-o <filename>]\n\n"
      "where:\n"
      "  -n <number>           Number of grid cells\n"
      "  -T <time>             Time interval 0 <= t <= T\n"
      "  -a <velocity>         Constant velocity\n"
      "  -o <filename>         Solution output filename\n",
      argv[0]); 
      return(0);
  }
  
  i = 1;
  
  while (i < argc) {
  
    /* Extract number of grid cells */
    if (!strcmp(argv[i], "-n")) {
      *n = atoi(argv[++i]);
    }
  
    /* Extract time span (0 <= t <= T) */
    if (!strcmp(argv[i], "-T")) {
      *T = atof(argv[++i]);
    }
    
    /* Extract the constant velocity  */
    if (!strcmp(argv[i], "-a")) {
      *a = atof(argv[++i]);
    }
    
    /* Extract the output filename (pointer) */
    if (!strcmp(argv[i], "-o")) {
      *file = (char *) malloc(sizeof(char) * (strlen(argv[i + 1]) + 1));  
      strcpy(*file, argv[++i]);
    }
    
    i++;
  }
 
  if (i != 9) {
  
    printf("-n, -T, -a and -o options must be specified\n");
    return(0);
  }
  
  return(1);
  
} /* get_args */

int main(int argc, char **argv) {
/*******************************************************************************
 FUNCTION : main
  
 LAST MODIFIED : Feb 24, 2005
 
 DESCRIPTION : One-dimensional advection equation.
 
==============================================================================*/

  char *file;
  int m, n, numprocs, rank;
  double *u, a, T, startwtime, endwtime;
  
  /* MPI initialization */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    
  if (rank == 0) {  
    
    /* Parse command line arguments */
    if (!get_args(argc, argv, &n, &T, &a, &file)) {
      return(0);
    }
  }
  
  /* Broadcast parameters (implicit barrier) */
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&T, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  
  /* Allocate data arrays (with ghost cell) */
  m = n / numprocs + 2;
  u = (double *) calloc(m, sizeof(double));
 
  if (rank == 0) startwtime = MPI_Wtime();
  
  /* Solve the advection equation */
  advection(m, n, numprocs, rank, T, u, a); 

  if (rank == 0) {
    endwtime = MPI_Wtime();
    printf("wall clock time = %f\n", endwtime - startwtime);
  }
  
  /* Clean up */
  free(u);

  MPI_Finalize();

  return(1);

} /* main */
