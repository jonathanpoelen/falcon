#include <test/test.hpp>
#include <falcon/functional/a.hpp>
#include "a.hpp"

void a_test()
{
  const int i0 = 1;
  const int i1 = 2;
  const int i2 = 3;

  STATIC_ASSERT(falcon::a0(i0, i1, i2) == i0);
  STATIC_ASSERT(falcon::a1(i0, i1, i2) == i1);
  STATIC_ASSERT(falcon::a2(i0, i1, i2) == i2);
  STATIC_ASSERT(falcon::alast(i0, i1, i2) == i2);
  STATIC_ASSERT(falcon::a<-2>()(i0, i1, i2) == i1);
  STATIC_ASSERT(falcon::a<-3>()(i0, i1, i2) == i0);
}

FALCON_TEST_TO_MAIN(a_test)
