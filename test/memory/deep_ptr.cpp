#include <test/test.hpp>
#include <falcon/memory/deep_ptr.hpp>
#include "deep_ptr.hpp"
#include <sstream>

void deep_ptr_test()
{
  struct A {
    std::ostream & os;
    int i;

    A(std::ostream & os, int i)
    : os(os)
    , i(i)
    { os << ">" << i << "\n"; }

    A(const A & a)
    : os(a.os)
    , i(a.i+100)
    { os << ">" << i << "\n"; }

    A(A && a)
    : os(a.os)
    , i(a.i+10)
    { os << ">" << i << "\n"; }

    ~A()
    { os << "<" << i << "\n"; }
    };

  std::ostringstream os;

  {
  falcon::deep_ptr<A> p = falcon::make_deep<A>(os, 1);
  falcon::deep_ptr<A> p2(p);
  falcon::deep_ptr<A> p3(std::move(p));
  p = p2;
  p3 = std::move(p2);
  }

  CHECK_EQUAL_VALUE(">1\n>101\n<1\n<101\n", os.str());
}

FALCON_TEST_TO_MAIN(deep_ptr_test)
