
#pragma once

#include "mat2dFloat.h"
namespace gp257{

class rescale2D{
  public:
    rescale2D(const int rescale): _rescale(rescale){;}
    void forward(const mat2DFloat &mod,  mat2DFloat &dat);
    void adjoint(mat2DFloat &mod, const  mat2DFloat &dat);

  private:
    int _rescale;
    std::vector< std::vector<int> > _ind1,_ind;
    std::vector< std::vector<float> > _f1,_f2;

};

}
