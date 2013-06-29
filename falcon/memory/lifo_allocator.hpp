#ifndef FALCON_MEMORY_LIFO_ALLOCATOR_HPP
#define FALCON_MEMORY_LIFO_ALLOCATOR_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/memory/allocator_rebind.hpp>
#include <falcon/memory/allocator_swap.hpp>

#include <memory>
#if __cplusplus > 201100L
#include <utility>
#else
#include <algorithm>
#endif

namespace falcon {

template <typename T, typename AllocBase = std::allocator<T> >
class lifo_allocator
: public allocator_rebind<AllocBase, T>::type
{
  typedef typename allocator_rebind<AllocBase, T>::type __allocator_base;

public:
  typedef typename __allocator_base::pointer pointer;
  typedef typename __allocator_base::size_type size_type;

#if __cplusplus > 201100L
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;
#endif

  template<typename U, typename AllocBase2 = AllocBase>
  struct rebind
  { typedef lifo_allocator<U, AllocBase2> other; };

public:
  lifo_allocator(T * first, T * last)	CPP_NOEXCEPT_OPERATOR2(__allocator_base())
  : __allocator_base()
  , m_current(first)
  , m_finish(last)
  {}

#if __cplusplus > 201100L
  lifo_allocator(const lifo_allocator&) = delete;
  lifo_allocator(lifo_allocator&&) noexcept = default;
  lifo_allocator& operator=(const lifo_allocator&) = delete;
  lifo_allocator& operator=(lifo_allocator&&) noexcept = default;
#else
private:
  lifo_allocator(const lifo_allocator&);
  lifo_allocator& operator=(const lifo_allocator&);
public:
#endif

  ~lifo_allocator() CPP_NOEXCEPT
  {}

  pointer allocate(size_type n, const void * = 0)
  {
    if (m_current + n > m_finish)
      throw std::bad_alloc();
    m_current += n;
    return reinterpret_cast<pointer>(m_current-n);
  }

  void deallocate(pointer p, size_type n) CPP_NOEXCEPT
  {
    (void)p;
    m_current -= n;
  }

  void swap(lifo_allocator& other) CPP_NOEXCEPT
  {
    std::swap<>(m_current, other.m_current);
    std::swap<>(m_finish, other.m_finish);
    allocator_swap<__allocator_base>(*this, other);
  }

  bool operator==(const lifo_allocator& other) const
  { return this == &other; }

  bool operator!=(const lifo_allocator& other) const
  { return this != &other; }

private:
  T * m_current;
  T * m_finish;
};

template<typename T, typename AllocBase>
bool operator==(const falcon::lifo_allocator<T, AllocBase>& a,
                const falcon::lifo_allocator<T, AllocBase>& b)
{ return &a == &b; }

template<typename T, typename AllocBase>
bool operator!=(const falcon::lifo_allocator<T, AllocBase>& a,
                const falcon::lifo_allocator<T, AllocBase>& b)
{ return &a != &b; }

}

namespace std {
  template<typename T, typename AllocBase>
  void swap(falcon::lifo_allocator<T, AllocBase>& a,
            falcon::lifo_allocator<T, AllocBase>& b)
  { a.swap(b); }
}

#endif
