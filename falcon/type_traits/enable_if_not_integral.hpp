#ifndef _FALCON_TYPE_TRAITS_ENABLE_IF_NOT_INTEGRAL_HPP
#define _FALCON_TYPE_TRAITS_ENABLE_IF_NOT_INTEGRAL_HPP

#if __cplusplus >= 201103L
# include <type_traits>

namespace falcon {
template<typename _T, typename _Result = _T>
struct enable_if_not_integral
{
	typedef typename std::enable_if<
		!std::is_integral<_T>::value, _Result
	>::type type;
};
}
#else
# include <boost/type_traits/is_integral.hpp>
# include <boost/utility/enable_if.hpp>

namespace falcon {
template<typename _T, typename _Result = _T>
struct enable_if_not_integral
: public boost::enable_if_c<!boost::is_integral<_T>::value, _Result>
{};
}
#endif

#endif