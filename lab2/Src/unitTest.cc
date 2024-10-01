#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <math.h>
#include<vector1d.h>
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test_vec )
{
  
  std::vector<float> test(3,1.);
  test[1]=2; test[2]=3;
  vector1d x(test);
    // seven ways to detect and report the same error:
    BOOST_REQUIRE(fabs( x.dot(x) - 14.)< .001 );        // #1 check to see if creted correctly and dot works

  std::vector<float> test2(3,-1.);
  test2[1]=-2; test2[2]=-3;
  vector1d y(test2);
   x.add(y); 
    BOOST_REQUIRE( fabs(x.dot( x )) < .001 );     

    y.scale(2.);
   BOOST_REQUIRE(fabs(y.dot(y)-56.)<.001) ;

}
