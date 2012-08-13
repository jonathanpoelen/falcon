#ifndef _FALCON_TYPE_TRAITS_SCALAR_HPP
#define _FALCON_TYPE_TRAITS_SCALAR_HPP

#include <type_traits>
#include <falcon/type_traits/scalar_rank.hpp>

namespace falcon {

template<std::size_t _Size>
struct size_in_scalar
{
	static const bool value =
		sizeof(char) == _Size ||
		sizeof(short) == _Size ||
		sizeof(int) == _Size ||
		sizeof(float) == _Size ||
		sizeof(long) == _Size ||
		sizeof(double) == _Size ||
		sizeof(long long) == _Size ||
		sizeof(long double) == _Size;
};

template<std::size_t _Size, typename _T>
struct __get_scalar
{
	typedef typename __get_scalar<_Size, typename scalar_rank_to_type<scalar_rank<_T>::value+1>::type>::type type;
};

#define _FALCON_MAKE_GET_SCALAR(_Type)\
	template<>\
	struct __get_scalar<sizeof(_Type), _Type>\
	{ typedef _Type type; };

_FALCON_MAKE_GET_SCALAR(char)
_FALCON_MAKE_GET_SCALAR(short)
_FALCON_MAKE_GET_SCALAR(int)
_FALCON_MAKE_GET_SCALAR(long)
_FALCON_MAKE_GET_SCALAR(long long)
_FALCON_MAKE_GET_SCALAR(float)
_FALCON_MAKE_GET_SCALAR(double)
_FALCON_MAKE_GET_SCALAR(long double)

#undef _FALCON_MAKE_GET_SCALAR

template<std::size_t _Size, bool _FloatingPoint = false>
struct get_scalar
: __get_scalar<_Size, char>
{};

template<std::size_t _Size>
struct get_scalar<_Size, true>
: __get_scalar<_Size, float>
{};

template<std::size_t _Size>
struct get_integral
: get_scalar<_Size>
{};

template<std::size_t _Size>
struct get_floating_point
: get_scalar<_Size, true>
{};

}

#endif
