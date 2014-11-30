#ifndef FALCON_FN_AT_HPP
#define FALCON_FN_AT_HPP

#include <falcon/fn/make_global_function_object.hpp>
#include <falcon/helper/use_size_type.hpp>
#include <falcon/type_traits/use_if.hpp>
#include <falcon/type_traits/use.hpp>

#include <stdexcept>

namespace falcon {
namespace fn {

namespace adl_ {
  template<class T, std::size_t N>
  constexpr T const & at(T const (&arr)[N], std::size_t i)
  {
    return (i >= N
      ? throw std::out_of_range("fn::adl_::at")
      : void()) , arr[i];
  }

  template<class T, std::size_t N>
  constexpr T & at(T (&arr)[N], std::size_t i)
  {
    return (i >= N
      ? throw std::out_of_range("fn::adl_::at")
      : void()) , arr[i];
  }
}

FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_ARGS(
  adl_, at, (class = void),
  (use_if_t<use_size_type<T>, use<std::size_t>> i), (i))

/// \brief call if possible, non member function at(T, size_t), otherwise T::at(size_t)
typedef adl_::at_fn at_fn;

}
}

#endif
