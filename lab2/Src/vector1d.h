#pragma once
#include<vector.h>
#include<vector>

class vector1d: public vector{
  public:
   vector1d(const std::vector<float> &v);
    vector1d(const long long nelem);
    virtual void add(const vector &vec2);
    virtual void scale(const float sc2);
    virtual vector *clone() const;
    virtual double dot(const vector &vec2)const;
    virtual bool checkSame(const  vector&vec2) const;
    virtual float *ptr(){return &_vec[0];}
    virtual const float *cptr() const {return &_vec[0];}
  private:
    std::vector<float> _vec;


};