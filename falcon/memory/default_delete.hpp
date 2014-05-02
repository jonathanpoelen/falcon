#ifndef FALCON_MEMORY_DEFAULT_DELETE_HPP
#define FALCON_MEMORY_DEFAULT_DELETE_HPP

#include <falcon/c++/boost_or_std.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <boost/type_traits/remove_extent.hpp>
# include <boost/type_traits/remove_pointer.hpp>
#endif
#include <iterator>


namespace falcon {

#if __cplusplus >= 201103L
template<typename T>
struct default_delete
: std::default_delete<T>
{};
#else
template<typename T>
struct default_delete
{
  void operator()(T* p) const
  { delete p; }
};

template<typename T>
struct default_delete<T[]>
{
  void operator()(T* p) const
  { delete[] p; }
};
#endif

template<typename T, std::size_t N>
struct default_delete<T[N]>
: default_delete<T[]>
{};


template<typename T>
struct default_delete_then_zero
{
  void operator()(typename FALCON_BOOST_OR_STD_NAMESPACE::remove_extent<T>::type * & p) const
  {
    default_delete<T>()(p);
    p = 0;
  }
};


template<typename ForwardIterator>
void default_deleter(ForwardIterator first, ForwardIterator last)
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_pointer<
    typename std::iterator_traits<ForwardIterator>::value_type
  >::type pointer;
  default_delete<pointer> deleter;
  for (; first != last; ++first) {
    deleter(*first);
  }
}

template<typename ForwardIterator>
void default_deleter_then_zero(ForwardIterator first, ForwardIterator last)
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_pointer<
    typename std::iterator_traits<ForwardIterator>::value_type
  >::type pointer;
  default_delete_then_zero<pointer> deleter;
  for (; first != last; ++first) {
    deleter(*first);
    *first = 0;
  }
}

}

#endif
