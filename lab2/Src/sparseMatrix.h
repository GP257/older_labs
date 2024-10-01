#pragma once
#include<matrix.h>
#include<vector>
class sparseMatrix:public matrix{
  public:
   sparseMatrix(const long long ndomain,const  long long nrange);
   
   virtual void applyForard(const vector & domain,
       vector &range) const;
    virtual void applyAdjoint(const vector &range,
       vector &domain) const;
    virtual bool checkLogical(const vector &domain,
      const vector &range) const;




};
