#ifndef FALCON_MEMORY_DESTROY_HPP
#define FALCON_MEMORY_DESTROY_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/memory/addressof.hpp>
#include <falcon/type_traits/integral_constant.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
# include <iterator>
#endif

namespace falcon {

/**
 * Destroy the object pointed to by a pointer type.
 */
CPP_GLOBAL_CONSTEXPR struct destroy_t {
  template<class T>
  void operator()(T * p) const
  { p->~T(); }

  template<class T, std::size_t N>
  void operator()(T (* p)[N]) const
  { operator()(*p, N); }

  template<class T>
  void operator()(T * p, std::size_t n) const
  {
    for (T * ep = p + n; p != ep; ++p) {
      operator()(p);
    }
  }

  template<class T>
  void operator()(T & p) const
  { p.~T(); }

  template<class T, std::size_t N>
  void operator()(T (& p)[N]) const
  { operator()(p, N); }

  /**
  * Destroy a range of objects. If the value_type of the object has
  * a trivial destructor, the compiler should optimize all of this
  * away, otherwise the objects' destructors must be invoked.
  */
  template<class ForwardIterator>
  void operator()(ForwardIterator first, ForwardIterator last) const
  {
    destroy_aux(integral_constant<bool,
#if __cplusplus >= 201103L
      std::is_trivially_destructible<
        typename std::iterator_traits<ForwardIterator>::value_type
      >::value
#else
      false
#endif
    >(), first, last);
  }

  template<class ForwardIterator, class Allocator>
  void operator()(ForwardIterator first, ForwardIterator last, Allocator& alloc) const
  {
    for (; first != last; ++first) {
      alloc.destroy(*first);
    }
  }

private:
  template<class ForwardIterator>
  void destroy_aux(
    integral_constant<bool, false>, ForwardIterator first, ForwardIterator last) const
  {
    for (; first != last; ++first) {
      operator()(falcon::addressof(*first));
    }
  }

  template<class ForwardIterator>
  void destroy_aux(integral_constant<bool, true>, ForwardIterator, ForwardIterator)
  const CPP_NOEXCEPT
  {}
} destroy;

}

#endif
