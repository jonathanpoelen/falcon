#include <test/test.hpp>
#include <test/A.h>
#include <falcon/memory/free_list.hpp>
#include "free_list.hpp"
#include "test_allocator.hpp"
#include <sstream>

void free_list_test()
{
  std::ostringstream os;
  typedef falcon::free_list<A, test_allocator<A> > free_list_type;
  free_list_type alloc(1, os);

  A * a1 = alloc.alloc();
  CHECK_EQUAL_VALUE("alloc\n", os.str());
  alloc.free(a1);
  A * a2 = alloc.alloc();
  CHECK_EQUAL_VALUE("alloc\n", os.str());
  A * a3 = alloc.alloc();
  CHECK_EQUAL_VALUE("alloc\nalloc\n", os.str());
  alloc.free(a2);
  A * a4 = alloc.alloc();
  CHECK_EQUAL_VALUE("alloc\nalloc\n", os.str());
  alloc.free(a4);
  alloc.free(a3);
  CHECK_EQUAL_VALUE("alloc\nalloc\n", os.str());

  free_list_type alloc2(1, os);
  alloc2.free(alloc2.alloc());
  CHECK_EQUAL_VALUE("alloc\nalloc\nalloc\n", os.str());
  alloc.merge(alloc2);
  alloc.clear();
  CHECK_EQUAL_VALUE("alloc\nalloc\nalloc\ndealloc\ndealloc\ndealloc\n", os.str());
  alloc2.clear();
  CHECK_EQUAL_VALUE("alloc\nalloc\nalloc\ndealloc\ndealloc\ndealloc\n", os.str());
}

FALCON_TEST_TO_MAIN(free_list_test)
