#include <cmath>
#include "boost/multi_array.hpp"
#include "timer.h"

typedef boost::multi_array<float, 3> float3D;

int main(int argc, char **argv){
long long n1=510,n2=510,n3=510;
int nt=20;
float vconst=2;

   float dsamp=.01,dt=.002;
   float sc=dt*dt/dsamp/dsamp;
   float coef[6];
   int ic1=n1/2,ic2=n2/2,ic3=n3/2;
   coef[1]=.83333333*sc;
   coef[2]=-.119047619*sc;
   coef[3]=.0198412698*sc;
   coef[4]=.00248015873*sc;
   coef[5]=.0001587301587*sc;
   coef[0]=-6*(coef[1]+coef[2]+coef[3]+coef[4]+coef[5]);
   
   std::vector<float>source(nt,0.);
   for(int it=0;it < nt; it++) source[it]=sin(it*3.1415926536/20.);
   
  std::shared_ptr<float3D> vsq(new float3D(boost::extents[n3][n2][n1]));
  std::shared_ptr<float3D> p1(new float3D(boost::extents[n3][n2][n1]));
  std::shared_ptr<float3D> p2(new float3D(boost::extents[n3][n2][n1]));
  std::shared_ptr<float3D> p3(new float3D(boost::extents[n3][n2][n1]));
  std::shared_ptr<float3D> oldW=p1;
  std::shared_ptr<float3D> curW=p2;
  std::shared_ptr<float3D> newW=p3,tmp;

  for(long long i=0; i < n1*n2*n3;  i++){
    oldW->data()[i]=0;
    curW->data()[i]=0;
    vsq->data()[i]=vconst*vconst;
  }

  timer x=timer("BIG LOOP",n1*n2*n3/1000);
  
  for(int it=0; it < nt; it++){
  fprintf(stderr,"it %d\n",it);
  x.start();
  
     #pragma omp parallel for default(shared)
     for(int i3=5; i3 < n3-5; i3++){
       for(int i2=5; i2 < n2-5; i2++){
         for(int i1=5; i1 < n1-5; i1++){
             (*newW)[i3][i2][i1]= 
            /*LAP*/
              (*vsq)[i3][i2][i1]*(coef[0]*(*curW)[i3][i2][i1]+
              coef[1]*(
                 (*curW)[i3][i2][i1-1]+(*curW)[i3][i2][i1+1]+
                 (*curW)[i3][i2-1][i2]+ (*curW)[i3][i2+1][i1]+
                 (*curW)[i3-1][i2][i2]+ (*curW)[i3+1][i2][i1])+
              coef[2]*(
                 (*curW)[i3][i2][i1-2]+(*curW)[i3][i2][i1+2]+
                 (*curW)[i3][i2-2][i2]+ (*curW)[i3][i2+2][i1]+
                 (*curW)[i3-2][i2][i2]+ (*curW)[i3+2][i2][i1])+
               coef[3]*(
                 (*curW)[i3][i2][i1-3]+(*curW)[i3][i2][i1+3]+
                 (*curW)[i3][i2-3][i2]+ (*curW)[i3][i2+3][i1]+
                 (*curW)[i3-3][i2][i2]+ (*curW)[i3+3][i2][i1])+
              coef[4]*(
                 (*curW)[i3][i2][i1-4]+(*curW)[i3][i2][i1+4]+
                 (*curW)[i3][i2-4][i2]+ (*curW)[i3][i2+4][i1]+
                 (*curW)[i3-4][i2][i2]+ (*curW)[i3+4][i2][i1])+
              coef[5]*(
                 (*curW)[i3][i2][i1-5]+(*curW)[i3][i2][i1+5]+
                 (*curW)[i3][i2-5][i2]+ (*curW)[i3][i2+5][i1]+
                 (*curW)[i3-5][i2][i2]+ (*curW)[i3+5][i2][i1]))+
                 2*(*curW)[i3][i2][i1]-(*oldW)[i3][i2][i1];
            }
        }
     }
     
	 /*Source*/
     (*newW)[ic3][ic2][ic1]+=source[it];
     
	 tmp=oldW; oldW=curW; curW=newW; newW=tmp;
	 
	 x.stop();
   }
   
   x.print() ;
  
  float m=newW->data()[0],mm=newW->data()[0];
  for(long long i=1; i < n1*n2*n3;  i++){
   if(newW->data()[i]>mm) mm=newW->data()[i];  
   if(newW->data()[i]<mm) m=newW->data()[i];  
  }
  fprintf(stderr,"min %f max %f\n",m,mm);

}
