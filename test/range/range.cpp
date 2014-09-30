#include <test/test.hpp>
#include <falcon/range/range.hpp>
#include "range.hpp"

void range_test()
{
  std::ostringstream ss;
  {
    auto cont = falcon::range(0,10);
    ss.clear();
    std::copy(cont.begin(), cont.end(), std::ostream_iterator<int>(ss, ","));
    CHECK_EQUAL_VALUE(ss.str(), "0,1,2,3,4,5,6,7,8,9,");
  }
  {
    auto cont = falcon::range(0,9, 2);
    ss.clear();
    std::copy(cont.begin(), cont.end(), std::ostream_iterator<int>(ss, ","));
    CHECK_EQUAL_VALUE(ss.str(), "0,2,4,6,8,");
  }
  int a[]{0, 1, 2, 3, 4, 5};
  {
    auto cont = falcon::range(a);
    ss.clear();
    std::copy(cont.begin(), cont.end(), std::ostream_iterator<int>(ss, ","));
    CHECK_EQUAL_VALUE(ss.str(), "0,1,2,3,4,5");
  }
  {
    auto cont = falcon::range(a, 2);
    ss.clear();
    std::copy(cont.begin(), cont.end(), std::ostream_iterator<int>(ss, ","));
    CHECK_EQUAL_VALUE(ss.str(), "0,2,4");
  }
  {
    auto cont = falcon::range(std::begin(a), 3);
    ss.clear();
    std::copy(cont.begin(), cont.end(), std::ostream_iterator<int>(ss, ","));
    CHECK_EQUAL_VALUE(ss.str(), "0,1,2");
  }
  {
    auto cont = falcon::range(std::begin(a), 3, 2);
    ss.clear();
    std::copy(cont.begin(), cont.end(), std::ostream_iterator<int>(ss, ","));
    CHECK_EQUAL_VALUE(ss.str(), "0,2");
  }
}

FALCON_TEST_TO_MAIN(range_test)
