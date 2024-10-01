

#include "hypercube.h"
using namespace gp257;
hypercube::hypercube(const std::vector<int> &ns){
  for(auto n: ns) _axes.push_back(axis(n));
   calcN123();
}
hypercube::hypercube(const hypercube &hyper){
  std::vector<axis> axes=hyper.getAxes();
  for(auto a: axes) _axes.push_back(axis(a));
   calcN123() ;
}
hypercube::hypercube(const std::vector<axis> &axes){
  for(auto a: axes) _axes.push_back(axis(a));
   calcN123() ;
}
hypercube::hypercube(const axis &ax1){
   _axes.push_back(axis(ax1));
   calcN123() ;
}
hypercube::hypercube(const axis &ax1, const axis &ax2){
   _axes.push_back(axis(ax1));
   _axes.push_back(axis(ax2));
   calcN123() ;
}
void hypercube::calcN123(){
  _n123=1;
  for(auto ax: _axes) _n123*=(long long) ax.n;
}
const std::vector<axis> hypercube::getAxes()const{
  std::vector<axis> axes;
  for(auto ax: _axes) axes.push_back(ax);
  return axes; 
}
const axis hypercube::getAxis(const int iax)const{
  return _axes[iax];
}
















