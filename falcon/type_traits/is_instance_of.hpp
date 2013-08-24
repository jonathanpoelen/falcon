#ifndef FALCONTYPETRAITS_IS_INSTANCE_OF_HPP
#define FALCONTYPETRAITS_IS_INSTANCE_OF_HPP

#if __cplusplus >= 201103L
#include <type_traits>

namespace falcon {
/**
 * determine if the type @p T is an instantiation of a @p U,
 * or @p T derives from an instantiation of @p U.
 */
template<typename T, typename U>
using is_instance_of = std::is_base_of<U, T>;
}
#else
#include <falcon/sfinae/sfinae.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename T, typename U>
class __is_instance_of
: falcon::sfinae_type
{
  static one __test(U*);
  static two __test(...);

public:
  static const bool value = sizeof(__test(static_cast<T*>(0))) == sizeof(one);
};

/**
 * determine if the type @p T is an instantiation of a @p U,
 * or @p T derives from an instantiation of @p U.
 */
template<typename T, typename U>
struct is_instance_of
: integral_constant<bool, __is_instance_of<T, U>::value>
{};

}
#endif

#endif
