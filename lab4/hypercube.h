#include<vector>
#include "axis.h"
namespace gp257{
class hypercube{
  public:
   hypercube(const std::vector<int> &n);
   hypercube(const std::vector<gp257::axis> &axes);
   hypercube(const gp257::axis &a1); 
   hypercube(const gp257::axis &a1, const gp257::axis &a2); 
   hypercube(const gp257::hypercube &hyper);
   const axis getAxis(const int iax) const;
   const std::vector<gp257::axis> getAxes() const;
   int getNdim() const {return _axes.size();}
   void calcN123() ;
   long long getN123()const{ return _n123;}
  private:
    std::vector<gp257::axis> _axes;
    long long  _n123;
};
}