#include <test/test.hpp>
#include <vector>
#include <array>
#include <type_traits>
#include <falcon/container/range_access_traits.hpp>
#include "range_access_traits.hpp"

void range_access_traits_test()
{
  typedef std::array<int, 3> container1;
  typedef std::vector<int> container2;

  container1 c1;
  container2 c2;

  CHECK_NOTYPENAME_TYPE(
    container1::iterator
  , decltype(falcon::range_access_traits::begin(c1)));

  CHECK_NOTYPENAME_TYPE(
    container2::iterator
  , decltype(falcon::range_access_traits::begin(c2)));

  container1 const & cc1 = c1;
  container2 const & cc2 = c2;

  CHECK_NOTYPENAME_TYPE(
    container1::const_iterator
  , decltype(falcon::range_access_traits::begin(cc1)));

  CHECK_NOTYPENAME_TYPE(
    container2::const_iterator
  , decltype(falcon::range_access_traits::begin(cc2)));

  CHECK(c1.begin() == falcon::range_access_traits::begin(c1));
  CHECK(cc1.cbegin() == falcon::range_access_traits::begin(cc1));
}

FALCON_TEST_TO_MAIN(range_access_traits_test)
