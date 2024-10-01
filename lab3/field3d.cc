#include<field3d.h>
#include<stdio.h>
#include<iostream>
field3d::field3d(const int n1, const int n2,const  int n3){
  allocate(n1,n2,n3);
}
void field3d::allocate(const int n1,const  int n2,const  int n3){

  std::vector<float> v1(n3,0.);

  std::vector<std::vector<float> > v2(n2,v1);

  _vals.resize(n1,v2);     


}

field3d::field3d(const int n1,const  int n2,const  int n3,const  float val){
   allocate(n1,n2,n3);
   for(int i3=0; i3 < n3; i3++){
     for(int i2=0; i2 < n2; i2++){
       for(int i1=0; i1 < n1; i1++){
          _vals[i1][i2][i3]=val;
        }
      }
    }

}
field3d::field3d(const field3d&f){
  mat3d vals=f.getCVals();
  
  std::vector<int> ns=f.getSize();
  
  int n1=vals.size();
  int n2=vals[0].size();
  int n3=vals[0][0].size();
  
  allocate(n1,n2,n3);
    for(int i3=0; i3 < n3; i3++){
     for(int i2=0; i2 < n2; i2++){
       for(int i1=0; i1 < n1; i1++){
          _vals[i1][i2][i3]=vals[i1][i2][i3];
        }
      }
    }
}
std::vector<int> field3d::getSize() const{
  std::vector<int> ns;
  ns.push_back(_vals.size());
  ns.push_back(_vals[0].size());

  ns.push_back(_vals[0][0].size());

  return ns;
}
field3d::field3d(const int n1, const int n2,const  int n3, 
const std::vector<int> ipos, const std::vector<int> off1,
const std::vector<int> off2, const std::vector<int> off3,
     const  std::vector<float> vals){
      
  allocate(n1,n2,n3);
  for(int i=0; i < off1.size(); i++)
    _vals[off1[i]+ipos[0]][off2[i]+ipos[1]][off3[i]+ipos[2]]=vals[i];     
      
      
      
}
field3d operator-(const field3d a, const field3d b){

   std::vector<int> ns=a.getSize();
   const mat3d as=a.getCVals(),bs=b.getCVals();
   field3d c(ns[0],ns[1],ns[2]);
   mat3d cs=c.getVals();
      for(int i3=0; i3 < ns[2]; i3++){
     for(int i2=0; i2 < ns[1]; i2++){
       for(int i1=0; i1 < ns[0]; i1++){
          cs[i1][i2][i3]=as[i1][i2][i3]-bs[i1][i2][i3];
        }
      }
    }
  return c;
}
field3d operator+(const field3d a, const field3d b){

   std::vector<int> ns=a.getSize();
   const mat3d as=a.getCVals(),bs=b.getCVals();
   field3d c(ns[0],ns[1],ns[2]);
   mat3d cs=c.getVals();
      for(int i3=0; i3 < ns[2]; i3++){
     for(int i2=0; i2 < ns[1]; i2++){
       for(int i1=0; i1 < ns[0]; i1++){
          cs[i1][i2][i3]=as[i1][i2][i3]+bs[i1][i2][i3];
        }
      }
    }
  return c;
}
float field3d::sum() const{
 std::vector<int> ns=getSize();
 float sm=0;
 for(int i3=0; i3 < ns[2]; i3++){
   for(int i2=0;i2 < ns[1]; i2++){
     for(int i1=0;i1 < ns[0]; i1++){
        sm+=_vals[i1][i2][i3];
      }
     }
    }
  return sm;
}



field3d operator*(const field3d a, const field3d b){
   std::vector<int> ns=a.getSize();
   const mat3d as=a.getCVals(),bs=b.getCVals();
   field3d c(ns[0],ns[1],ns[2]);
   mat3d cs=c.getVals();
      for(int i3=0; i3 < ns[2]; i3++){
     for(int i2=0; i2 < ns[1]; i2++){
       for(int i1=0; i1 < ns[0]; i1++){
          cs[i1][i2][i3]=as[i1][i2][i3]*bs[i1][i2][i3];
        }
      }
    }
    return c;
}
field3d operator*(const field3d a, const float b){
   std::vector<int> ns=a.getSize();
   const mat3d as=a.getCVals();
   field3d c(ns[0],ns[1],ns[2]);
   mat3d cs=c.getVals();
      for(int i3=0; i3 < ns[2]; i3++){
     for(int i2=0; i2 < ns[1]; i2++){
       for(int i1=0; i1 < ns[0]; i1++){
          cs[i1][i2][i3]=as[i1][i2][i3]*b;
        }
      }
    }
    return c;
}
field3d operator*(const float b, const field3d a){

   std::vector<int> ns=a.getSize();
   const mat3d as=a.getCVals();
   field3d c(ns[0],ns[1],ns[2]);
   mat3d cs=c.getVals();
      for(int i3=0; i3 < ns[2]; i3++){
     for(int i2=0; i2 < ns[1]; i2++){
       for(int i1=0; i1 < ns[0]; i1++){
          cs[i1][i2][i3]=as[i1][i2][i3]*b;
        }
      }
    }
    return c;
}