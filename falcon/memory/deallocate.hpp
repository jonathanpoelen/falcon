#ifndef FALCON_MEMORY_DEALLOCATE_HPP
#define FALCON_MEMORY_DEALLOCATE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(remove_extent)
#include <new>

namespace falcon {

template<class T>
struct default_deallocate
{
  CPP_CONSTEXPR default_deallocate() {}

  void operator()(T* p, std::size_t = 1) const
  CPP_NOEXCEPT_OPERATOR2(::operator delete(p))
  { ::operator delete(p); }
};

template<class T>
struct default_deallocate<T[]>
{
  CPP_CONSTEXPR default_deallocate() {}

  void operator()(T* p, std::size_t = 1) const
  CPP_NOEXCEPT_OPERATOR2(::operator delete[](p))
  { ::operator delete[](p); }
};


template<class T>
struct default_deallocate_then_null
{
  CPP_CONSTEXPR default_deallocate_then_null() {}

  void operator()(
    typename FALCON_BOOST_OR_STD_NAMESPACE::remove_extent<T>::type * & p,
    std::size_t = 1) const
  CPP_NOEXCEPT_OPERATOR2(default_deallocate<T>()(p))
  {
    default_deallocate<T>()(p);
#if __cplusplus >= 201103L
    p = nullptr;
#else
    p = 0;
#endif
  }
};


CPP_GLOBAL_CONSTEXPR struct deallocate_ptr_t {
  CPP_CONSTEXPR deallocate_ptr_t() {}

  template<class T>
  void operator()(T * p, std::size_t = 1) const
  { default_deallocate<T>()(p); }
} deallocate_ptr;

CPP_GLOBAL_CONSTEXPR struct deallocate_array_t {
  CPP_CONSTEXPR deallocate_array_t() {}

  template<class T>
  void operator()(T * p, std::size_t = 1) const
  { default_deallocate<T[]>()(p); }
} default_deallocate_array;


CPP_GLOBAL_CONSTEXPR struct deallocate_ptr_then_null_t {
  CPP_CONSTEXPR deallocate_ptr_then_null_t() {}

  template<class T>
  void operator()(T * & p, std::size_t = 1) const
  { default_deallocate_then_null<T>()(p); }
} deallocate_ptr_then_null;

CPP_GLOBAL_CONSTEXPR struct deallocate_array_then_null_t {
  CPP_CONSTEXPR deallocate_array_then_null_t() {}

  template<class T>
  void operator()(T * & p, std::size_t = 1) const
  { default_deallocate_then_null<T[]>()(p); }
} deallocate_array_then_null;


template<class T>
void deallocate(T * ptr, std::size_t n = 1)
{ default_deallocate<T>()(ptr, n); }

template<class T>
void deallocate_array(T * ptr, std::size_t n = 1)
{ default_deallocate<T[]>()(ptr, n); }


template<class ForwardIterator>
void deallocater(ForwardIterator first, ForwardIterator last)
{
  for (; first != last; ++first) {
    deallocate_ptr(*first);
  }
}

template<class ForwardIterator>
void deallocater_then_null(ForwardIterator first, ForwardIterator last)
{
  for (; first != last; ++first) {
    deallocate_ptr_then_null(*first);
  }
}

}

#endif
