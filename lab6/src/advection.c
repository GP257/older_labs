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

int advection(int n, double T, double *u, double a) {
/*******************************************************************************
 FUNCTION : advection
  
 LAST MODIFIED : Feb 24, 2006
 
 DESCRIPTION : Solves the one-dimensional advection equation using upwinding
   and explicit Euler discretization.
 
==============================================================================*/

  int i, s, t;
  double gamma, sum, *v, x;
  
  delta_t delta;

  /* Solution at next time step */
  v = (double *) malloc(sizeof(double) * (n + 1));

  /* Spatial discretization */
  delta.x = 1.0 / (double) n;

  /* Time step satisfying CFL condition */
  delta.t = delta.x / a;
  gamma = a * delta.t / delta.x;
  
  /* Boundary conditions u(0, t) */
  u[0] = 0;

  /* Initial conditions (t = 0). There are numerous ways to define the 
     initial solution (without the if statement), however this form is ideal 
     for the MPI implementation
  */
  
  /* Global x coordinate */
  x = delta.x;
  for (i = 1; i < n - 2; i++) {
    
    if (x >= 0.0 && x <= 0.2) {
      u[i] = 1 - pow(10.0 * x - 1.0, 2.0); 
    }
    x += delta.x;
  }
   
  /* Loop over time (indices) */
  s = (int) (T / delta.t);
  for (t = 0; t < s; t++) {
  
    /* Loop over space */
    for (i = 1; i < n; i++) {
      v[i] = u[i] - gamma * (u[i] - u[i - 1]); 
    }
    
    /* Update solution */
    for (i = 1; i < n; i++) {
      u[i] = v[i]; 
    }
  } 
  
  /* Exact solution */
  for (i = 0; i < n; i++) {
    v[i] = 0.0;
  }

  /* Global (x - at) coordinates */
  x = - a * T;
 
  for (i = 0; i <= n; i++) {
    if (x >= 0.0 && x <= 0.2) {
      v[i] = 1 - pow(10.0 * x - 1.0, 2.0); 
    }
    x += delta.x;
  }
  
  /* L-2 Error norm */
  sum = 0.0;
  
  for (i = 0; i < n; i++) {
    sum += pow(v[i] - u[i], 2.0);
  } 
  
  printf("residual error for n = %d is: %e\n", n, sqrt(sum)); 
  
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
  int i, n;
  double *u, a, T;  
  
  FILE *fid;
  time_t startwtime, endwtime;
  
  /* Parse command line arguments */
  if (!get_args(argc, argv, &n, &T, &a, &file)) {
    return(0);
  }

  /* Allocate data arrays */
  u = (double *) calloc(n + 1, sizeof(double));
 
  startwtime = time(&startwtime);
  
  /* Solve the advection equation */
  advection(n, T, u, a); 
 
  endwtime = time(&endwtime);
  printf("wall clock time = %f\n", difftime(endwtime, startwtime));
 
  /* Output solution to file */
  if (fid = fopen(file, "w")) {
    for (i = 0; i <= n; i++) {
      fprintf(fid, "%lf\n", u[i]);
    }
    fclose(fid);
  }
 
  /* Clean up */
  free(u);

  return(1);

} /* main */
