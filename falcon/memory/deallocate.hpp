#ifndef FALCON_MEMORY_DEALLOCATE_HPP
#define FALCON_MEMORY_DEALLOCATE_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(remove_extent)
#include <new>

namespace falcon {

template<class T>
struct deallocate
{
  void operator()(T* p, std::size_t = 1) const
  { ::operator delete(p); }
};

template<class T>
struct deallocate<T[]>
{
  void operator()(T* p, std::size_t = 1) const
  { ::operator delete[](p); }
};


template<class T>
struct deallocate_then_zero
{
  void operator()(
    typename FALCON_BOOST_OR_STD_NAMESPACE::remove_extent<T>::type * & p,
    std::size_t = 1) const
  {
    deallocate<T>()(p);
    p = 0;
  }
};


CPP_GLOBAL_CONSTEXPR struct deallocate_ptr_t {
  template<class T>
  void operator()(T * p, std::size_t = 1) const
  { deallocate<T>()(p); }
} deallocate_ptr;

CPP_GLOBAL_CONSTEXPR struct delete_array_t {
  template<class T>
  void operator()(T * p, std::size_t = 1) const
  { deallocate<T[]>()(p); }
} delete_array;


CPP_GLOBAL_CONSTEXPR struct deallocate_ptr_then_zero_t {
  template<class T>
  void operator()(T * & p, std::size_t = 1) const
  { deallocate_then_zero<T>()(p); }
} deallocate_ptr_then_zero;

CPP_GLOBAL_CONSTEXPR struct delete_array_then_zero_t {
  template<class T>
  void operator()(T * & p, std::size_t = 1) const
  { deallocate_then_zero<T[]>()(p); }
} delete_array_then_zero;


template<class ForwardIterator>
void deallocater(ForwardIterator first, ForwardIterator last)
{
  for (; first != last; ++first) {
    deallocate_ptr(*first);
  }
}

template<class ForwardIterator>
void deallocater_then_zero(ForwardIterator first, ForwardIterator last)
{
  for (; first != last; ++first) {
    deallocate_ptr_then_zero(*first);
  }
}

}

#endif
