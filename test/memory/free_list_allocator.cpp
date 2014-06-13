#include <test/test.hpp>
#include <test/A.h>
#include <falcon/memory/free_list_allocator.hpp>
#include "free_list_allocator.hpp"
#include "test_allocator.hpp"

void free_list_allocator_test()
{
  typedef falcon::free_list_allocator<A, test_allocator<A> > allocator_type;
  allocator_type alloc(1, std::cout);

  A * a1 = alloc.allocate(1);
  alloc.deallocate(a1);

  alloc.freelist().get_allocator();
}

FALCON_TEST_TO_MAIN(free_list_allocator_test)
