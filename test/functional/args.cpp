#include <test/test.hpp>
#include <falcon/functional/args.hpp>
#include "args.hpp"

void args_test()
{
  const int i0 = 1;
  const int i1 = 2;
  const int i2 = 3;

  CHECK((falcon::args<2, 0>()(i0, i1, i2) == std::make_tuple(i2, i0)));
  CHECK((falcon::args<-1, -2>()(i0, i1, i2) == std::make_tuple(i2, i1)));
}

FALCON_TEST_TO_MAIN(args_test)
