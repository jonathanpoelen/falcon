#include <test/test.hpp>
#include <falcon/functional/invoke.hpp>
#include "invoke.hpp"

void invoke_test()
{
  CHECK(falcon::invoke([](int i){return i;}, 2) == 2);
  CHECK(falcon::invoke(
    falcon::parameter_index<1>()
  , [](int i){return i;}, 1, 2, 3)
  == 2);

  struct S {
    int f(int i) { return i; }
  } s;

  CHECK(falcon::invoke(&S::f, &s, 2) == 2);
  CHECK(falcon::invoke(falcon::parameter_index<1>(), &S::f, &s, 1, 2, 3) == 2);
}

FALCON_TEST_TO_MAIN(invoke_test)
