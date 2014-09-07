#ifndef FALCON_MEMORY_LIFO_ALLOCATOR_HPP
#define FALCON_MEMORY_LIFO_ALLOCATOR_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/memory/allocator_rebind.hpp>
#include <falcon/memory/allocator_swap.hpp>
#include <falcon/memory/non_owner_ptr.hpp>

#include <memory>
#if __cplusplus >= 201103L
# include <falcon/type_traits/is_nothrow_swap.hpp>
# include <utility>
#else
# include <algorithm>
#endif

#include <cassert>

namespace falcon {

template <typename T, typename AllocBase = std::allocator<T> >
class lifo_allocator
: public allocator_rebind<AllocBase, T>::type
{
  typedef typename allocator_rebind<AllocBase, T>::type allocator_base;

public:
  typedef typename allocator_base::pointer pointer;
  typedef typename allocator_base::size_type size_type;

#if __cplusplus >= 201103L
private:
  using allocator_base_traits = std::allocator_traits<allocator_base>;

public:
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment
    = typename allocator_base_traits::propagate_on_container_move_assignment;
  using propagate_on_container_swap = typename allocator_base_traits::propagate_on_container_swap;
#endif

  template<typename U, typename AllocBase2 = AllocBase>
  struct rebind
  { typedef lifo_allocator<U, AllocBase2> other; };

public:
  lifo_allocator(T * first, T * last)
  CPP_NOEXCEPT_OPERATOR2(allocator_base())
  : allocator_base()
  , m_current(first)
  , m_finish(last)
  {}

#if __cplusplus >= 201103L
  lifo_allocator(const lifo_allocator&) = delete;
  lifo_allocator(lifo_allocator&&) = default;
  lifo_allocator& operator=(const lifo_allocator&) = delete;
  lifo_allocator& operator=(lifo_allocator&&) = default;
#else
private:
  lifo_allocator(const lifo_allocator&);
  lifo_allocator& operator=(const lifo_allocator&);
public:
#endif

  pointer allocate(size_type n, const void * = 0)
  {
    if (m_current + n > m_finish)
      throw std::bad_alloc();
    m_current += n;
    return reinterpret_cast<pointer>(m_current-n);
  }

  void deallocate(pointer p, size_type n) CPP_NOEXCEPT
  {
    assert(p + n == m_current);
    (void)p;
    m_current -= n;
  }

  void swap(lifo_allocator& other)
  CPP_NOEXCEPT(is_nothrow_swap<allocator_base>::value)
  {
    using std::swap;
    swap(m_current, other.m_current);
    swap(m_finish, other.m_finish);
    allocator_swap<allocator_base>(*this, other);
  }

  size_type max_size() const
  { return m_finish - m_current; }

  bool operator==(const lifo_allocator& other) const noexcept
  { return this == &other && base() == other.base(); }

  bool operator!=(const lifo_allocator& other) const noexcept
  { return !(this == &other); }

private:
  non_owner_ptr<T> m_current;
  non_owner_ptr<T> m_finish;

  allocator_base & base() const noexcept
  { return *this; }
};

template<typename T, typename AllocBase>
void swap(lifo_allocator<T, AllocBase>& a, lifo_allocator<T, AllocBase>& b)
CPP_NOEXCEPT(is_nothrow_swap<lifo_allocator<T, AllocBase>>::value)
{ a.swap(b); }

}

#endif
