#pragma once
#include<vector.h>
class matrix{

  public:
    matrix(){;}
    void setDomainRange(const long long nd, const long long nr);
    virtual void applyForard(const vector & domain,
       vector &range) const;
    virtual void applyAdjoint(const vector &range,
       vector &domain) const;
    virtual bool checkLogical(const vector &domain,
      const vector &range) const;
     long long getNDomain() const { return _ndomain;}
     long long getNRange()const {return _nrange;}
  private:
    long long _ndomain;
    long long _nrange;

};