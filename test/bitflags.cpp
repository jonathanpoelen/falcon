#include <sstream>
#include <iomanip>
#include <falcon/bitflags.hpp>
#include "test.hpp"
#include "bitflags.hpp"

void bitflags_test()
{
  falcon::bitflags<int> f;
  f += (1 << 0);
  f += (1 << 8);
  f += (1 << 5);
  CHECK_EQUAL_VALUE(f, (1 << 0) | (1 << 5) | (1 << 8));
  f -= (1 << 0);
  f -= (1 << 0);
  CHECK_EQUAL_VALUE(f, (1 << 5) | (1 << 8));
  CHECK_EQUAL_VALUE(f[0], true);
  CHECK_EQUAL_VALUE(f[1], false);
  CHECK_EQUAL_VALUE(f[2], false);
  CHECK_EQUAL_VALUE(f[3], false);
  CHECK_EQUAL_VALUE(f[4], false);
  CHECK_EQUAL_VALUE(f[5], true);
  CHECK_EQUAL_VALUE(f[6], false);
  CHECK_EQUAL_VALUE(f[7], false);
  CHECK_EQUAL_VALUE(f[8], true);
  CHECK_EQUAL_VALUE(f[9], false);
  CHECK_EQUAL_VALUE(f.to_ulong(), unsigned(f.get()));
}
FALCON_GROUP_TEST_TO_MAIN(bitflags_test)
