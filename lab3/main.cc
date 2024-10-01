#include<field3d.h>
#include<prop.h>
#include<stdio.h>
int main(int argc, char **argv){
   int n1=100,n2=100,n3=100;
   float vconst=2000.;
   vel3d vel(n1,.01,n2,.01,n3,.01,vconst);
   std::vector<float> coef(5,0.);
   coef[0]=.83333333;
   coef[1]=-.119047619;
   coef[2]=.0198412698;
   coef[3]=.00248015873;
   coef[4]=.0001587301587;
   
   field3d prev(n1,n2,n3);
   field3d cur(n1,n2,n3);

   

   
   std::vector<int> isrc(3,50);
   prop p(.002,vel,isrc,coef);
   
   for(int it=0; it < 500; it++){
     {

       fprintf(stderr,"working on iteration %d \n",it);
        field3d next=p.advance(prev,cur,it);
        prev=cur;
        cur=next;
      }
   
   }


}
