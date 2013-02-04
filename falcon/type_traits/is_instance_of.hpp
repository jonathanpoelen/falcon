#ifndef FALCON_TYPE_TRAITS_IS_INSTANCE_OF_HPP
#define FALCON_TYPE_TRAITS_IS_INSTANCE_OF_HPP

#include <falcon/sfinae/sfinae.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename _T, typename _U>
class __is_instance_of
: falcon::sfinae_type
{
	static one __test(_U*);
	static two __test(...);

public:
	static const bool value = sizeof(__test(static_cast<_T*>(0))) == 1;
};

/**
 * determine if the type @p _T is an instantiation of a @p _U,
 * or @p _T derives from an instantiation of @p _U.
 */
template<typename _T, typename _U>
struct is_instance_of
: integral_constant<bool, __is_instance_of<_T, _U>::value>
{};

}

#endif