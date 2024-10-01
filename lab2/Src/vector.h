#pragma once
#include <assert.h>
class vector{
  public:
   vector(){;}
   virtual void add(const vector& vec2){assert(1==2);}
   virtual void scale(const float sc){ assert(1==2);}
   virtual vector *clone() const;
   virtual double dot(const vector *vec2){assert(1==2);}
   void setNelem(const long n){ _nelem=n;}
   long long getNelem() const {return _nelem;}
   bool checkSame(const  vector&vec2) const { assert(1==2);}
   virtual float *ptr(){assert(1==2);}
   virtual const float *cptr() const {assert(1==2);} 
  private:
    long long _nelem;
};