#include <test/test.hpp>
#include <falcon/iostreams/multibuf.hpp>
#include "multibuf.hpp"

void multibuf_test()
{
  std::stringbuf b1("123"), b2("4 5 6"), b3("7 8");
  falcon::iostreams::multibuf mb({&b1, &b2, &b3});

  std::ostream out(&mb);
  out << 9;
  out << '8';
  mb.pnext();
  out << '1';

  int i;
  std::istream in(&mb);
  std::ostringstream oss;
  while (in >> i) {
    oss << i << '\n';
  }

  CHECK_EQUAL_VALUE("9831\n5\n67\n8\n", oss.str());

  mb.get_generator() = {&b1, &b2, &b3};
  char cb[10]{0};
  CHECK_EQUAL_VALUE(0, mb.sgetn(cb, 2));

  b1.pubseekpos(0);
  b2.pubseekpos(0);
  //b3.pubseekpos(0);
  mb.get_generator() = {&b1, &b2, &b3};
  CHECK_EQUAL_VALUE(2, mb.sgetn(cb, 2));
  CHECK_EQUAL_VALUE(6, mb.sgetn(cb+2, 7));
  CHECK_EQUAL_VALUE(std::string("9831 5 6"), cb);
}

FALCON_TEST_TO_MAIN(multibuf_test)
