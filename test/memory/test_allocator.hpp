#ifndef TEST_MEMORY_TEST_ALLOCATOR_HPP
#define TEST_MEMORY_TEST_ALLOCATOR_HPP

#include <memory>
#include <iosfwd>

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

#endif
