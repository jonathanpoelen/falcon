#include <test/test.hpp>
#include <falcon/memory/lifo_allocator.hpp>
#include "lifo_allocator.hpp"
#include <test/A.h>
#include <iterator>

void lifo_allocator_test()
{
  int data[10];
  falcon::lifo_allocator<int> l(std::begin(data), std::end(data));
  int * p1 = l.allocate(2);
  int * p2 = l.allocate(3);
  int * p3 = l.allocate(4);
  try {
    l.allocate(5);
    CHECK(0);
  }
  catch (std::bad_alloc const &) {
  }
  int * p5 = l.allocate(1);
  l.deallocate(p5, 1);
  l.deallocate(p3, 4);
  l.deallocate(p2, 3);
  l.deallocate(p1, 2);
}

FALCON_TEST_TO_MAIN(lifo_allocator_test)
