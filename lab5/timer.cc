#include "timer.h"
#include<iostream>


void timer::print() const{
  double totTime=(double)_totTime.count();
  if(_opsSet){
    double speed= (double) _ncalls*(double) _ops/totTime;
    std::cerr<<_name<<std::string(" totTime=")<<std::to_string(static_cast<long long>(_totTime.count()))<<std::string(" milliseconds Ncalls=")<<std::to_string(static_cast<long long>(_ncalls))<<std::string(" Mcells/Sec=")<<std::to_string(static_cast<long double>(speed))<<std::endl;
  
  }
  else
   std::cerr<<_name<<std::string(" totTime=")<<std::to_string(static_cast<long double>(totTime))<<std::string(" calls=")<<std::to_string(static_cast<long long>(_ncalls))<<std::endl;
  

}


void timer::start(){
  
_start = high_resolution_clock::now();
}
void timer::stop(){
  _totTime+=std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - _start);
  _ncalls+=1;

}
    
