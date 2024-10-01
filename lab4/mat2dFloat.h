#include "boost/multi_array.hpp"
#include <cassert>
#include "hypercube.h"

typedef boost::multi_array<float, 2> float2D;
namespace gp257{
class mat2DFloat{
  public:
    mat2DFloat(const gp257::hypercube &hyp);

    std::unique_ptr<float2D> _vals;
    const std::shared_ptr<gp257::hypercube> getHyper() const {return _hyper;}
  private:
    std::shared_ptr<gp257::hypercube> _hyper;
};
}
