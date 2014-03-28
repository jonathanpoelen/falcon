#include <test/test.hpp>
#include <falcon/memory/default_new.hpp>
#include <falcon/memory/deallocate.hpp>
#include <falcon/memory/construct.hpp>
#include <falcon/memory/allocate.hpp>
#include <falcon/memory/destroy.hpp>
#include "construct.hpp"

#include <array>
#include <memory>

void construct_test()
{
  struct A
  {
    int x;
  };

  class B
  {
  public:
    int a,b;
    B(int x, int y)
    : a(x)
    , b(y)
    {}
  };

  using C = std::array<int, 3>;

  using D = int[2][2];

  A * p1 = falcon::default_new<A>()(2);
  B * p2 = falcon::default_new<B>()(4,3);
  A * p3 = falcon::default_new<A[2]>()(A{1},A{7});
  C * p4 = falcon::default_new<C>()(5,6,8);
  D aa {{1, 2}, {3, 4}};
  D * p5 = falcon::allocate<D>()();
  falcon::construct(p5, aa);

  CHECK(p1->x == 2);
  CHECK(p2->a == 4);
  CHECK(p2->b == 3);
  CHECK(p3[0].x == 1);
  CHECK(p3[1].x == 7);
  CHECK((*p4)[0] == 5);
  CHECK((*p4)[1] == 6);
  CHECK((*p4)[2] == 8);
  CHECK((*p5)[0][0] == 1);
  CHECK((*p5)[0][1] == 2);
  CHECK((*p5)[1][0] == 3);
  CHECK((*p5)[1][1] == 4);

  std::default_delete<A>()(p1);
  std::default_delete<B>()(p2);
  std::default_delete<A[]>()(p3);
  std::default_delete<C>()(p4);
  falcon::destroy(p5);
  falcon::deallocate<D>()(p5);
}

FALCON_TEST_TO_MAIN(construct_test)
