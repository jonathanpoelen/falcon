#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/container/unordered_container_view.hpp>
#include "unordered_container_view.hpp"
#include <vector>

void unordered_container_view_test()
{
  std::vector<int> vxx{{1,2,3,4}};
  falcon::unordered_container_view<std::vector<int>> v(vxx);
  v.insert(5);
  v.insert(2);
  {
    int ab [] = {1,2,3,4,5,2};
    CHECK_SEQUENCE3(ab, vxx);
  }
  v.remove(2);
  {
    int ab [] = {1,5,3,4};
    CHECK_SEQUENCE3(ab, vxx);
  }
}

FALCON_TEST_TO_MAIN(unordered_container_view_test)
