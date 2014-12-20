#include <test/test.hpp>
#include <falcon/iostreams/iofmts.hpp>
#include "iofmts.hpp"
#include <sstream>

void iofmts_test()
{
  using namespace falcon::iostreams::iofmts;

  std::ostringstream oss;
  oss << hex(10) << ' ' << 10;
  CHECK(oss.str() == "a 10");
}

FALCON_TEST_TO_MAIN(iofmts_test)
