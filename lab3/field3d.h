#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<stdio.h>
typedef  std::vector<std::vector<std::vector<float > > > mat3d;
class field3d{
  public:
    field3d(){;}
    field3d(const int n1,const  int n2,const  int n3);
    field3d(const int n1, const int n2,const  int n3,const  float val);
    field3d(const field3d &f);
    field3d(const int n1,const  int n2,const  int n3,
    const std::vector<int> pos,
    const  std::vector<int> off1,const std::vector<int> off2, const std::vector<int> off3,
      const std::vector<float> vals);
    field3d &operator*=(const field3d &a){
       std::vector<int> ns=a.getSize();
       const mat3d as=a.getCVals();
       allocate(ns[0],ns[1],ns[2]);
       for(int i3=0; i3 < ns[2]; i3++){
         for(int i2=0; i2 < ns[1]; i2++){
            for(int i1=0; i1 < ns[0]; i1++){
              _vals[i1][i2][i3]*=as[i1][i2][i3];
            }
         }
       }
       return *this;
   } 
   float sum() const;   
    field3d &operator+=(const field3d &a){
      fprintf(stderr,"in += \n");
       std::vector<int> ns=a.getSize();
       const mat3d as=a.getCVals();
       allocate(ns[0],ns[1],ns[2]);
       for(int i3=0; i3 < ns[2]; i3++){
       for(int i2=0; i2 < ns[1]; i2++){
         for(int i1=0; i1 < ns[0]; i1++){
          _vals[i1][i2][i3]+=as[i1][i2][i3];
         }
       }
      }
      return *this;
    }
    const mat3d getCVals() const{ return _vals;}
    mat3d getVals(){ return _vals;}

    std::vector<int> getSize() const;
     void allocate(const int n1,const  int n2, const int n3);

  private:
     mat3d _vals;
    

};
    field3d operator+(const field3d a, const field3d b);
    field3d operator-(const field3d a, const field3d b);

    field3d operator*(const field3d a, const field3d b);
    field3d operator*(const field3d a, const float b);
    field3d operator*(const float b,const field3d a);