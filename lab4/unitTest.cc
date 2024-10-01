#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <stdlib.h>
#include <math.h>
#include <rescale.h>
#include <boost/test/unit_test.hpp>

using namespace gp257;

BOOST_AUTO_TEST_CASE(test_rescale)
{
	//test forward
   int n1=2,n2=2;

   axis a1(n1),a2(n2);
   int fact=2;

   rescale2D res(fact);

   hypercube hin(a1,a2);
   axis a1o=axis((n1-1)*fact),a2o=axis((n2-1)*fact);
   hypercube hout(a1o,a2o);

   mat2DFloat mod=mat2DFloat(hin),dat=mat2DFloat(hout);
    
   for(int  i2=0; i2 < n2; i2++){
     for(int i1=0; i1 < n1; i1++){
         (*mod._vals)[i2][i1]=i1+i2*2.;
       }
     }

	res.forward(mod,dat);

	BOOST_REQUIRE((*dat._vals)[0][0]==0. && (*dat._vals)[1][0]==1. && (*dat._vals)[0][1]==.5 && (*dat._vals)[1][1]==1.5);

	//dot product test

	int m1=rand()%100,m2=rand()%100,factor=rand()%10;
	int m1o=(m1-1)*factor,m2o=(m2-1)*factor;
	
	rescale2D A(factor);
	
	axis b1(m1),b2(m2),b1o(m1o),b2o(m2o);
	
	hypercube hm(b1,b2),hd(b1o,b2o);

	mat2DFloat x=mat2DFloat(hm),Ax=mat2DFloat(hd),y=mat2DFloat(hd),Aty=mat2DFloat(hm);

	#pragma omp parallel for default(shared)
	for(int i2=0;i2<m2;++i2){
     for(int i1=0;i1<m1;++i1){
      (*x._vals)[i2][i1]=(float)rand()/(float)RAND_MAX;
	 }
	}

	A.forward(x,Ax);
	
	#pragma omp parallel for default(shared)
	for(int i2=0;i2<m2o;++i2){
     for(int i1=0;i1<m1o;++i1){
      (*y._vals)[i2][i1]=(float)rand()/(float)RAND_MAX;
	 }
	}
	
	A.adjoint(Aty,y);
	
	double yAx=0.;
	#pragma omp parallel for default(shared) reduction(+:yAx)
	for(int i2=0;i2<m2o;++i2){
     for(int i1=0;i1<m1o;++i1){
	  yAx+=(*y._vals)[i2][i1]*(*Ax._vals)[i2][i1];
	 }
	}

	double Atyx=0.;
	#pragma omp parallel for default(shared) reduction(+:Atyx)
	for(int i2=0;i2<m2;++i2){
     for(int i1=0;i1<m1;++i1){
	  Atyx+=(*Aty._vals)[i2][i1]*(*x._vals)[i2][i1];
	 }
	}

    fprintf(stderr,"%f %f\n",yAx,Atyx);
 	BOOST_REQUIRE(fabs(yAx-Atyx)<0.001);

}
