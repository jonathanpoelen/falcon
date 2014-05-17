#ifndef FALCON_CONTAINER_CONTAINS_RANGE_ACCESS_HPP
#define FALCON_CONTAINER_CONTAINS_RANGE_ACCESS_HPP

#include <falcon/container/range_access.hpp>
#include <falcon/sfinae/function_is_callable.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {
  namespace _aux {
    FALCON_FUNCTION_IS_CALLABLE_TRAIT_DEF(begin);
    FALCON_FUNCTION_IS_CALLABLE_TRAIT_DEF(rbegin);
  }

  template <class T>
  struct contains_range_access_iterator
  : integral_constant<bool, _aux::begin_is_callable<T&>::value>
  {};

  template <class T>
  struct contains_range_access_reverse_iterator
  : integral_constant<bool, _aux::rbegin_is_callable<T&>::value>
  {};
}

#endif
