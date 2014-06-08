#include <test/test.hpp>
#include <test/A.h>
#include <falcon/memory/free_list.hpp>
#include "free_list.hpp"
#include <sstream>

template<typename T, typename AllocBase = std::allocator<T> >
class test_allocator
: public std::allocator_traits<AllocBase>::template rebind_alloc<T>
{
  typedef typename std::allocator_traits<AllocBase>::template rebind_alloc<T> allocator_base;

public:
  typedef typename allocator_base::pointer pointer;
  typedef typename allocator_base::size_type size_type;

  template<typename U, typename NewAllocBase = AllocBase>
  struct rebind
  { typedef test_allocator<U, NewAllocBase> other; };

  test_allocator(std::ostream & os)
  : os(os)
  {}

  template<class U, class AllocOther>
  test_allocator(test_allocator<U, AllocOther> const &other)
  : os(other.os)
  {}

  pointer allocate(size_type n, const void * p = 0)
  {
    os << "alloc\n";
    return allocator_base::allocate(n, p);
  }

  void deallocate(pointer p, size_type n)
  {
    os << "dealloc\n";
    return allocator_base::deallocate(p, n);
  }

  std::ostream & os;
};

void free_list_test()
{
  std::ostringstream os;
  falcon::free_list<A, test_allocator<A>> alloc(1, os);

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
  alloc.clear();
  CHECK_EQUAL_VALUE("alloc\nalloc\ndealloc\ndealloc\n", os.str());
}

FALCON_TEST_TO_MAIN(free_list_test)
