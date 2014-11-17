#ifndef FALCON_CONTAINER_CONTAINS_RANGE_ACCESS_HPP
#define FALCON_CONTAINER_CONTAINS_RANGE_ACCESS_HPP

#include <falcon/helper/has_iterator.hpp>
#include <falcon/helper/has_const_iterator.hpp>
#include <falcon/helper/has_reverse_iterator.hpp>
#include <falcon/helper/has_const_reverse_iterator.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {
  namespace aux_ {
    template <class T>
    struct contains_range_access_iterator
    : integral_constant<bool,
      (has_iterator<T>::value || has_const_iterator<T>::value)
    > {};

    template <class T>
    struct contains_range_access_iterator<const T>
    : has_const_iterator<T>
    {};

    template <class T>
    struct contains_range_access_reverse_iterator
    : integral_constant<bool,
      (has_reverse_iterator<T>::value || has_const_reverse_iterator<T>::value)
    > {};

    template <class T>
    struct contains_range_access_reverse_iterator<const T>
    : has_const_reverse_iterator<T>
    {};
  }

  template <class T>
  struct contains_range_access_iterator
  : aux_::contains_range_access_iterator<
    typename std::decay<T>::type
  > {};

  template <class T, std::size_t N>
  struct contains_range_access_iterator<T[N]>
  : true_type
  {};

  template <class T>
  struct contains_range_access_reverse_iterator
  : aux_::contains_range_access_reverse_iterator<
    typename std::decay<T>::type
  > {};

  template <class T, std::size_t N>
  struct contains_range_access_reverse_iterator<T[N]>
  : true_type
  {};
}

#endif
