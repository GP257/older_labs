#pragma once
#include<field3d.h>
class vel3d: public field3d{
  public:
    vel3d(){;}
    vel3d(const int n1, const float d1, const int n2, const float d2,
      const int n3, const float d3, float vconst);  
    vel3d(const vel3d &v);
    float getD1()const{return _d1;}
    float getD2()const{return _d2;}
    float getD3()const {return _d3;}
    
  private:
     float _d1,_d2,_d3;



};

class prop{
  public:
    prop(const float dt,const vel3d vel,std::vector<int> isrc,std::vector<float> coef);

    field3d advance( const field3d prev, const field3d cur,const int it) const;
    field3d applyLaplacian(const field3d cur) const;
   field3d sourceTerm(const int it) const;
  private:
    vel3d _vel;
    float _dt;
    std::vector<int> _isrc,_off1,_off2,_off3;
    std::vector<float> _coef;



};

