#include<matrix.h>

void matrix::setDomainRange(const long long nd, const long long nr){
  _ndomain=nd; 
  _nrange=nr;
}
void matrix::applyForard(const vector & domain, vector &range) const {
  assert(1==2);
}
void matrix::applyAdjoint(const vector &range, vector &domain) const{
 assert(1==2);
}
bool matrix::checkLogical(const vector &domain, const vector &range) const{
  assert(1==2);
}