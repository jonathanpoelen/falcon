#include <sstream>
#include <iomanip>
#include <falcon/flag.hpp>
#include "test.hpp"
#include "flag.hpp"

void flag_test()
{
  falcon::bitflag<unsigned> f;
  f += (1 << 0);
  f += (1 << 8);
  f += (1 << 5);
  CHECK_EQUAL_VALUE(f, (1 << 0) | (1 << 5) | (1 << 8));
  f -= (1 << 0);
  f -= (1 << 0);
  CHECK_EQUAL_VALUE(f, (1 << 5) | (1 << 8));
}
FALCON_GROUP_TEST_TO_MAIN(flag_test)
