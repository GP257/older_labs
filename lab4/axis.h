#include<string>
namespace gp257{
class axis{
  public:
   int n;
   float o;
   float d;
   std::string label;
    axis(const int nin): n(nin),o(0.),d(1.),label(std::string("none")){;}
    axis(const int nin, const float oin,const  float din): n(nin), o(oin), d(din), label(std::string("none")){;}
    axis(const int nin, const float oin, const float din, const std::string labelin): n(nin), o(oin), d(din), label(labelin){}
    axis(const axis &ax): n(ax.n), o(ax.o),d(ax.d),label(ax.label){;}

};
}
