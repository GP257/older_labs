#include<vector1d.h>
#include<iostream>

vector1d::vector1d(const std::vector<float>&b){
  _vec=b;
  setNelem(b.size());
}

vector1d::vector1d(const long long nelem){
    _vec.assign(nelem,0.);
    setNelem(nelem);
  }
void vector1d::add(const vector &vec2){
    if(!checkSame(vec2)) assert(1==2);
    const vector1d *cst=dynamic_cast<const vector1d*>(&vec2);
    for(long long i=0; i < _vec.size(); i++)
       _vec[i]+=cst->_vec[i];
    
  }
bool vector1d::checkSame(const vector &vec2) const {
    //First check to see if of the same type
    const vector1d *cst=dynamic_cast<const vector1d*>(&vec2);
    if(cst==NULL) {std::cerr<<"Not a vector1d"<<std::endl; return false;}
    if(cst->getNelem()!=getNelem()){
      std::cerr<<"Vector not the same size"<<std::endl;
      return false;
    }
    return true;
  }
void vector1d::scale(const float sc2) {
for(long long i=0; i < _vec.size(); i++)
       _vec[i]*=sc2;
}
vector *vector1d::clone() const{
  vector1d *x= new vector1d(getNelem());
  for(long long i=0; i < getNelem(); i++) x->_vec[i]=_vec[i];
  return x;
}
double vector1d::dot(const vector &vec2) const{
    if(!checkSame(vec2)) assert(1==2);
    const vector1d *cst=dynamic_cast<const vector1d*>(&vec2);
    double o=0;
    for(long long i=0; i < _vec.size(); i++)
       o+=_vec[i]*cst->_vec[i];
    return o;
}
