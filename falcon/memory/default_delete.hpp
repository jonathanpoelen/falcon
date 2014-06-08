#ifndef FALCON_MEMORY_DEFAULT_DELETE_HPP
#define FALCON_MEMORY_DEFAULT_DELETE_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
# include <memory>
#else
# include <boost/type_traits/remove_extent.hpp>
# include <boost/type_traits/remove_pointer.hpp>
#endif
#include <iterator>


namespace falcon {

#if __cplusplus >= 201103L
template<class T>
struct default_delete
: std::default_delete<T>
{};
#else
template<class T>
struct default_delete
{
  void operator()(T* p) const
  { delete p; }
};

template<class T>
struct default_delete<T[]>
{
  void operator()(T* p) const
  { delete[] p; }
};
#endif


template<class T>
struct default_delete_then_zero
{
  void operator()(typename FALCON_BOOST_OR_STD_NAMESPACE::remove_extent<T>::type * & p) const
  {
    default_delete<T>()(p);
    p = 0;
  }
};


CPP_GLOBAL_CONSTEXPR struct delete_ptr_t {
  template<class T>
  void operator()(T * p) const
  { default_delete<T>()(p); }
} delete_ptr;

CPP_GLOBAL_CONSTEXPR struct delete_array_t {
  template<class T>
  void operator()(T * p) const
  { default_delete<T[]>()(p); }
} delete_array;


CPP_GLOBAL_CONSTEXPR struct delete_ptr_then_zero_t {
  template<class T>
  void operator()(T * & p) const
  { default_delete_then_zero<T>()(p); }
} delete_ptr_then_zero;

CPP_GLOBAL_CONSTEXPR struct delete_array_then_zero_t {
  template<class T>
  void operator()(T * & p) const
  { default_delete_then_zero<T[]>()(p); }
} delete_array_then_zero;


template<class ForwardIterator>
void default_deleter(ForwardIterator first, ForwardIterator last)
{
  for (; first != last; ++first) {
    delete_ptr(*first);
  }
}

template<class ForwardIterator>
void default_deleter_then_zero(ForwardIterator first, ForwardIterator last)
{
  for (; first != last; ++first) {
    delete_ptr_then_zero(*first);
  }
}

}

#endif
