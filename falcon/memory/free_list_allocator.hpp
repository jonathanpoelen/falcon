#ifndef FALCON_MEMORY_FREE_LIST_ALLOCATOR_HPP
#define FALCON_MEMORY_FREE_LIST_ALLOCATOR_HPP

#include <falcon/memory/free_list.hpp>
#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/pack.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/utility/move.hpp>

namespace falcon {

template<class T, class AllocBase = std::allocator<T> >
class free_list_allocator
{
public:
  typedef typename ::falcon::free_list<T, AllocBase> free_list_type;
  typedef typename free_list_type::value_type value_type;
  typedef typename free_list_type::pointer pointer;
  typedef typename free_list_type::size_type size_type;
  typedef typename free_list_type::difference_type difference_type;
  typedef typename free_list_type::const_pointer const_pointer;
  typedef value_type & reference;
  typedef const value_type & const_reference;

#if __cplusplus >= 201103L
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::false_type;
#endif

  template<class U, class AllocBase2 = AllocBase>
  struct rebind
  { typedef free_list_allocator<U, AllocBase2> other; };

  explicit free_list_allocator(free_list_type const & flist)
  CPP_NOEXCEPT_OPERATOR2(free_list_type(flist))
  : free_list_(flist)
  {}

  explicit free_list_allocator(size_type size)
  CPP_NOEXCEPT_OPERATOR2(free_list_type(size))
  : free_list_(size)
  {}

  explicit free_list_allocator(const free_list_allocator& other)
  CPP_NOEXCEPT_OPERATOR2(free_list_type(other.count_by_alloc(), other.m_allocator))
  : free_list_(other.count_by_alloc(), other.m_allocator)
  {}

  template<class CPP_PACK Args>
  free_list_allocator(size_type size, Args CPP_RVALUE_OR_CONST_REFERENCE CPP_PACK args)
  CPP_NOEXCEPT_OPERATOR2(free_list_type(size, FALCON_FORWARD(Args, args)CPP_PACK))
  : free_list_(size, FALCON_FORWARD(Args, args)CPP_PACK)
  {}

#if __cplusplus >= 201103L
  explicit free_list_allocator(free_list_allocator&& other)
  CPP_NOEXCEPT_OPERATOR2(free_list_type(std::move(other.free_list_)))
  : free_list_(std::move(other.free_list_))
  {}

  explicit free_list_allocator(free_list_type && flist)
  CPP_NOEXCEPT_OPERATOR2(free_list_type(std::move(flist)))
  : free_list_(std::move(flist))
  {}
#endif

  template<class U, class AllocBase2>
  explicit free_list_allocator(const free_list_allocator<U, AllocBase2>& other)
  CPP_NOEXCEPT_OPERATOR2(free_list_type(other.count_by_alloc(), other.m_allocator))
  : free_list_(other.count_by_alloc(), other.m_allocator)
  {}

  free_list_allocator& operator=(const free_list_allocator& other) CPP_NOEXCEPT
  { return *this; }

  pointer allocate(const void * = 0)
  { return free_list_.alloc(); }

  pointer allocate(size_type n, const void * = 0)
  {
    (void)n;
    assert(free_list_.count_by_alloc() ==  n);
    return free_list_.alloc();
  }

  void deallocate(pointer p)
  { return free_list_.free(p); }

  void deallocate(pointer p, size_type n)
  {
    (void)n;
    assert(free_list_.count_by_alloc() ==  n);
    return free_list_.free(p);
  }

  free_list_type& freelist() CPP_NOEXCEPT
  { return free_list_; }

  const free_list_type& freelist() const CPP_NOEXCEPT
  { return free_list_; }

private:
  free_list_type free_list_;
};

template<class T, class AllocBase>
bool operator==(
  const free_list_allocator<T, AllocBase>& a
, const free_list_allocator<T, AllocBase>& b) CPP_NOEXCEPT
{ return a.free_list() == b.free_list(); }

template<class T, class AllocBase>
bool operator!=(
  const free_list_allocator<T, AllocBase>& a
, const free_list_allocator<T, AllocBase>& b) CPP_NOEXCEPT
{ return a.free_list() == b.free_list(); }

}

#endif
