#include<rescale.h>
#include<stdio.h>
#include<timer.h>
using namespace gp257;
int main(int argc, char **argv){
   int n1=800,n2=800;

   axis a1(n1),a2(n2);
   int fact=10;

   rescale2D res(fact);

   hypercube hin(a1,a2);
   axis a1o=axis((n1-1)*fact),a2o=axis((n2-1)*fact);
   hypercube hout(a1o,a2o);

  mat2DFloat mod=mat2DFloat(hin),dat=mat2DFloat(hout);
   
  for(int  i2=0; i2 < n2; i2++){
    float p2=(float)i2/(float)n2;
    for(int i1=0; i1 < n1; i1++){
      float p1=(float)i1/(float)n1;
        (*mod._vals)[i2][i1]=p1+p2*10.;
      }
    }
  
      

  timer fwd(std::string("forward")), adj(std::string("adjoint"));
  
  for(int i=0; i < 10; i++){
  fwd.start();
  res.forward(mod,dat);
  fwd.stop();
  
  adj.start();
  res.adjoint(mod,dat);
  adj.stop();
  }
  fwd.print();
  adj.print();
  
  


}