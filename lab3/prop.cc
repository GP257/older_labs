#include<prop.h>
#include<field3d.h>
#include<assert.h>
#include<math.h>
#include<stdio.h>
#include<timer.h>
vel3d::vel3d(const int n1, const float d1, const int n2, const float d2,
      const int n3, const float d3, float vconst){
   allocate(n1,n2,n3);
   mat3d cs=getVals();
   for(int i3=0; i3<n3; i3++){
     for(int i2=0; i2 < n2; i2++){
       for(int i1=0; i1 < n1; i1++){
          cs[i1][i2][i3]=vconst;
        }
      }
    }     
    _d1=d1;
    _d2=d2;
    _d3=d3;
      
}
vel3d::vel3d(const vel3d &v){
   std::vector<int> ns=v.getSize();
   allocate(ns[0],ns[1],ns[2]);
   mat3d cs=getVals();
   const mat3d as=v.getCVals();
   for(int i3=0; i3<ns[2]; i3++){
     for(int i2=0; i2 < ns[1]; i2++){
       for(int i1=0; i1 < ns[0]; i1++){
          cs[i1][i2][i3]=as[i1][i2][i3];
        }
      }
    }     
    _d1=v.getD1();
    _d2=v.getD2();
    _d3=v.getD3();
}
prop::prop(const float dt,const  vel3d  v, const std::vector<int> isrc,const std::vector<float> coef){

  _vel=vel3d(v);
  _dt=dt;
  _isrc=isrc;
  assert(coef.size()==5);
  std::vector<int> ns=v.getSize();
  float sm=0;
  for(int i=0; i <5 ; i++){
    _off1.push_back(i); _off2.push_back(0); _off3.push_back(0); _coef.push_back(coef[i]);
    _off1.push_back(0); _off2.push_back(i); _off3.push_back(0); _coef.push_back(coef[i]);
    _off1.push_back(0); _off2.push_back(0); _off3.push_back(i); _coef.push_back(coef[i]);
    _off1.push_back(-i); _off2.push_back(0); _off3.push_back(0); _coef.push_back(coef[i]);
    _off1.push_back(0); _off2.push_back(-i); _off3.push_back(0); _coef.push_back(coef[i]);
    _off1.push_back(0); _off2.push_back(0); _off3.push_back(-i); _coef.push_back(coef[i]);
    sm+=coef[i];
   }
   _off1.push_back(0); _off2.push_back(0); _off3.push_back(0);
   _coef.push_back(-2.*sm);
  
}
field3d prop::applyLaplacian(const field3d cur) const{
  std::vector<int> ns=cur.getSize();
  field3d lap(ns[0],ns[1],ns[2]);
  std::vector<int> pos(3,0);
  mat3d l=lap.getVals();
  timer tm(std::string("laplacian"),(ns[0]-10)); 
  for(int i3=5; i3 < ns[2]-5; i3++){
    
    for(int i2=5; i2 < ns[1]-5; i2++){
      tm.start();
      for(int i1=5; i1<ns[0]-5; i1++){
         pos[0]=i1; pos[1]=i2; pos[2]=i3;
         field3d filt(ns[0],ns[1],ns[2],pos,_off1,_off2,_off3,_coef);
         field3d temp(cur);
         temp=filt*cur;
         l[i1][i2][i3]=temp.sum();
       }
       tm.stop();
       tm.print();
    }
  }
  return lap;

}
field3d prop::sourceTerm(const int it) const{
  std::vector<int> ns=_vel.getSize();
  field3d source(ns[0],ns[1],ns[2]);
  mat3d s=source.getVals();
  s[_isrc[0]][_isrc[1]][_isrc[2]]=sin(it*3.1415926536/20.);
  return source;
}
field3d prop::advance(const field3d cur, const field3d prev,const int it) const{
   
  mat3d c=cur.getCVals(), p=prev.getCVals();

  field3d spaceDeriv=applyLaplacian(cur)*_vel*_vel;

  field3d next(cur);

  next=2.*cur-prev+(_dt*_dt*spaceDeriv)+sourceTerm(it);
  
 return next;
}
   
   


