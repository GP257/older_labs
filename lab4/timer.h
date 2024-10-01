#pragma once
#include <chrono>
#include <ctime>
#include<string>
typedef std::chrono::high_resolution_clock high_resolution_clock;
typedef std::chrono::milliseconds milliseconds;
class timer{
  public:
    timer(std::string name): _name(name), _opsSet(false),_ncalls(0),_totTime(0){;}
    timer(std::string name, int ops): _name(name), _opsSet(true), _ops(ops),_ncalls(0),_totTime(0){;}
    void print() const;
    void start();
    void stop();
  private:
    int _ops;
    high_resolution_clock::time_point _start;
    milliseconds _totTime;
    int _ncalls;
    bool _opsSet;
    std::string _name;


};





















