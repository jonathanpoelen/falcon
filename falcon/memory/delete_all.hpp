#ifndef FALCON_DELETE_ALL_HPP
#define FALCON_DELETE_ALL_HPP

#include <falcon/memory/destroy.hpp>
#include <falcon/container/range_access.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#else
#include <boost/type_traits/remove_pointer.hpp>
#endif

namespace falcon
{

#if __cplusplus >= 201103L

template<
  typename ForwardIterator,
  typename T = typename std::remove_pointer<
    typename std::iterator_traits<ForwardIterator>::value_type
  >::type
>
inline void delete_all(ForwardIterator first, ForwardIterator last)
{
  default_delete_wrapper<T> deleter;
  for (; first != last; ++first) {
    deleter(*first);
  }
}

template<
  typename Container,
  typename T = typename std::remove_pointer<
    typename range_access_subtype<Container>::type
  >::type
>
inline void delete_all(Container& container)
{
  typedef typename range_access_iterator<Container>::type iterator;
  delete_all<iterator, T>(begin(container), end(container));
}

#else

template<typename ForwardIterator>
inline void delete_all(ForwardIterator first, ForwardIterator last)
{
  default_delete_wrapper<
    typename boost::remove_pointer<
      typename std::iterator_traits<ForwardIterator>::value_type
    >::type
  > deleter;
  for (; first != last; ++first) {
    deleter(*first);
  }
}

template<typename Container>
inline void delete_all(Container& container)
{ delete_all(begin(container), end(container)); }

#endif

}

#endif
