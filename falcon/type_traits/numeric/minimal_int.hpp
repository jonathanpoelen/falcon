#ifndef FALCON_TYPE_TRAITS_NUMERIC_MINIMAL_INT_HPP
#define FALCON_TYPE_TRAITS_NUMERIC_MINIMAL_INT_HPP

#include <cstddef>
#include <falcon/type_traits/numeric/greater.hpp>

namespace falcon {
template<int Bytes>
struct __full_bits {
	template<int N, std::size_t n = 1ull>
	struct impl {
		static const std::size_t value = impl<N-1, (n << 1) | 1>::value;
	};
	template<std::size_t n>
	struct impl<1,n> {
		static const std::size_t value = n;
	};
	static const std::size_t value = impl<Bytes * __CHAR_BIT__>::value;
};

template<std::size_t choose, typename _Int, bool lower = (choose <= __full_bits<sizeof(_Int)>::value)>
struct __minimal_int;

template<std::size_t choose, typename _Int>
struct __minimal_int<choose, _Int, true>
{
	typedef _Int type;
};

template<std::size_t choose, typename _Int>
struct __minimal_int<choose, _Int, false>
: __minimal_int<choose, typename greater_int<_Int>::type>
{};

template<std::size_t choose>
struct __minimal_int<choose, bool, false>
: __minimal_int<choose, typename greater_int<bool>::type>
{};

template<std::size_t choose>
struct __minimal_int<choose, bool, true>
{
	typedef char type;
};

template<>
struct __minimal_int<1ull, bool, true>
{
	typedef bool type;
};

template<>
struct __minimal_int<2ull, bool, true>
{
	typedef bool type;
};

template<std::size_t choose, typename _BaseInt = unsigned char>
struct minimal_int
{
	typedef typename __minimal_int<choose, _BaseInt>::type type;
};

}

#endif
