#ifndef FALCON_LITERAL_UTILITY_HPP
#define FALCON_LITERAL_UTILITY_HPP

#include <falcon/literal/detail/literal_support.hpp>

#include <type_traits>
#include <limits>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/use.hpp>

namespace falcon {
namespace literal {

template<typename _CharT, _CharT c>
struct is_digit
: std::integral_constant<bool, (_CharT('0') <= c && c <= _CharT('9'))>
{};


template<std::size_t position>
struct check_false
: std::false_type
{ static const std::size_t last_position = position; };

template<std::size_t position>
struct check_true
: std::true_type
{ static const std::size_t last_position = position; };


template<std::size_t position, typename _CharT, _CharT... chars>
struct __is_integral_base_10;

template<std::size_t position, typename _CharT, _CharT c, _CharT... chars>
struct __is_integral_base_10<position, _CharT, c, chars...>
: if_c<
	is_digit<_CharT, c>,
	__is_integral_base_10<position + 1, _CharT, chars...>,
	check_false<position>
>::type
{ static const std::size_t last_position = position; };

template<std::size_t position, typename _CharT>
struct __is_integral_base_10<position, _CharT>
: check_true<position>
{};

template<typename _CharT, _CharT... chars>
struct is_integral
: __is_integral_base_10<0, _CharT, chars...>
{};

template<typename _CharT>
struct is_integral<_CharT>
: check_false<0>
{};


template<std::size_t position, typename _CharT, _CharT... chars>
struct __is_floating_point_base_10;

template<std::size_t position, typename _CharT, _CharT c, _CharT... chars>
struct __is_floating_point_base_10<position, _CharT, c, chars...>
: eval_if<
	c == _CharT('.'),
	use<__is_integral_base_10<position + 1, _CharT, chars...>>,
	if_c<
		is_digit<_CharT, c>,
		__is_floating_point_base_10<position + 1, _CharT, chars...>,
		check_false<position>
	>
>::type
{};

template<std::size_t position, typename _CharT>
struct __is_floating_point_base_10<position, _CharT>
: check_true<position>
{};

template<typename _CharT, _CharT... chars>
struct is_floating_point
: __is_floating_point_base_10<0, _CharT, chars...>
{};

template<typename _CharT>
struct is_floating_point<_CharT>
: check_false<0>
{};

template<typename _CharT, _CharT c>
struct is_floating_point<_CharT, c>
: if_<(c == _CharT('.')), check_false<1>, check_true<1>>::type
{};


template<typename _To, typename _CharT, _CharT... chars>
struct __check_convert_integral
{
	static_assert(is_integral<_CharT, chars...>::value, "value is not integral");
};

template<typename _To, unsigned long long ullvalue>
struct __to_value
{
	static_assert((ullvalue <= static_cast<unsigned long long>(std::numeric_limits<_To>::max())), "overflow in implicit constant conversion");
	static const _To __value = static_cast<_To>(ullvalue);
};

template<typename _To, _To value, typename _CharT, _CharT c>
struct __to_value_base_10
: __to_value<_To, value * 10 + (static_cast<_To>(c) - _To('0'))>
{};

template<typename _To, _To value, typename _CharT, _CharT... chars>
struct __convert_to_integral_base_10;

template<typename _To, _To value, typename _CharT, _CharT c, _CharT... chars>
struct __convert_to_integral_base_10<_To, value, _CharT, c, chars...>
: __convert_to_integral_base_10<
	_To,
	__to_value_base_10<_To, value, _CharT, c>::__value,
	_CharT,
	chars...
>
{ static_assert(is_digit<_CharT, c>(), "value is not integral"); };

template<typename _To, _To value, typename _CharT>
struct __convert_to_integral_base_10<_To, value, _CharT>
: std::integral_constant<_To, value>
{};

template<typename _To, typename _CharT, _CharT... chars>
struct __convert_to_integral
: __convert_to_integral_base_10<_To, _To(0), _CharT, chars...>
{ static_assert(sizeof...(chars), "value is empty"); };

template<bool, bool, typename _To, typename _CharT, _CharT... chars>
struct __convert_to;

template<typename _To, typename _CharT, _CharT... chars>
struct __convert_to<true, false, _To, _CharT, chars...>
: __convert_to_integral<_To, _CharT, chars...>
{};

// template<typename _To, typename _CharT, _CharT... chars>
// struct __convert_to<false, true, _To, _CharT, chars...>
// : __convert_to_floating_point<_To, _CharT, chars...>
// {};

template<typename _To, typename _CharT, _CharT... chars>
struct basic_convert_to
: __convert_to<
	std::is_integral<_To>::value,
	std::is_floating_point<_To>::value,
	_To, _CharT, chars...>
{};


template<typename _To, char... chars>
using convert_to = basic_convert_to<_To, char, chars...>;


template<char... chars>
using to_short = convert_to<short, chars...>;
template<char... chars>
using to_int = convert_to<int, chars...>;
template<char... chars>
using to_long = convert_to<long, chars...>;
template<char... chars>
using to_long_long = convert_to<long long, chars...>;
template<char... chars>
using to_ushort = convert_to<unsigned short, chars...>;
template<char... chars>
using to_uint = convert_to<unsigned int, chars...>;
template<char... chars>
using to_ulong = convert_to<unsigned long, chars...>;
template<char... chars>
using to_ulong_long = convert_to<unsigned long long, chars...>;


}
}

#endif
