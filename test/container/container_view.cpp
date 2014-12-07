#include <test/test.hpp>
#include <vector>
#include <algorithm>
#include <falcon/container/container_view.hpp>
#include "container_view.hpp"

void container_wrapper_test()
{
  typedef std::vector<int> array_type;
  array_type arr( {4,4,2,1});
  falcon::container_view<array_type> wrap(arr);
  CHECK_EQUAL_VALUE(4, (*wrap.begin())++);
  CHECK_EQUAL_VALUE(5, *wrap.begin());

  std::sort(wrap.begin(), wrap.end());
  CHECK_EQUAL_VALUE(1, *wrap.begin());
  CHECK_EQUAL_VALUE(2, *(wrap.begin()+1));
  CHECK_EQUAL_VALUE(4, *(wrap.begin()+2));
  CHECK_EQUAL_VALUE(5, *(wrap.begin()+3));

  falcon::reverse_container_view<array_type> rwrap(arr);
  std::sort(rwrap.begin(), rwrap.end());
  CHECK_EQUAL_VALUE(5, *wrap.begin());
  CHECK_EQUAL_VALUE(4, *(wrap.begin()+1));
  CHECK_EQUAL_VALUE(2, *(wrap.begin()+2));
  CHECK_EQUAL_VALUE(1, *(wrap.begin()+3));

  falcon::seq(arr);
  falcon::seq(wrap);
  falcon::cseq(arr);
  falcon::rseq(arr);
  falcon::crseq(arr);
}

FALCON_TEST_TO_MAIN(container_wrapper_test)
