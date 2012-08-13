#ifndef _FALCON_TYPE_TRAITS_NUMERIC_MINIMAL_BITS_HPP
#define _FALCON_TYPE_TRAITS_NUMERIC_MINIMAL_BITS_HPP

#include <limits>
#include <falcon/type_traits/numeric/greater.hpp>

namespace falcon {

template<unsigned int choose, typename _Int, bool lower = (choose <= unsigned(std::numeric_limits<_Int>::digits))>
struct __minimal_bits;

template<unsigned int choose, typename _Int>
struct __minimal_bits<choose, _Int, true>
{
	typedef _Int type;
};

template<unsigned int choose, typename _Int>
struct __minimal_bits<choose, _Int, false>
{
	typedef typename __minimal_bits<choose, typename greater_int<_Int>::type>::type type;
};

template<int choose, typename _BaseInt = unsigned char>
struct minimal_bits
{
	typedef typename __minimal_bits<choose, _BaseInt>::type type;
};

}

#endif
