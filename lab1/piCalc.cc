


#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include<stdio.h>
int main(int argc, char **argv){

  srand(atol(argv[1]));
  long long inside=0;
  long long todo=999939344;
  //long long todo=9939344;
  for(long long i=0; i < todo; i++){
   double x=(double)rand()/(RAND_MAX); 
   double y=(double)rand()/(RAND_MAX); 
   double e=x*x+y*y; 
   if(e<= 1.) inside+=1;
  }
  fprintf(stdout,"%.20e\n",4.*(double)inside/(double)todo);

}
