#include <test/test.hpp>
#include <test/check_sequence.hpp>
#include <falcon/container/unordered_vector.hpp>
#include "unordered_vector.hpp"

void unordered_vector_test()
{
  falcon::unordered_vector<int> v{{1,2,3,4}};
  v.insert(5);
  v.insert(2);
  {
    int ab [] = {1,2,3,4,5,2};
    CHECK_SEQUENCE3(ab, v);
  }
  v.remove(2);
  {
    int ab [] = {1,3,4,5};
    CHECK_SEQUENCE3(ab, v);
  }
}

FALCON_TEST_TO_MAIN(unordered_vector_test)
