#ifndef _FALCON_TYPE_TRAITS_SUBTYPE_HPP
#define _FALCON_TYPE_TRAITS_SUBTYPE_HPP

#ifndef __GXX_EXPERIMENTAL_CXX0X__
# include <boost/typeof/typeof.hpp>
#endif
#include <falcon/type_traits/declval.hpp>

namespace falcon {
template <typename _T>
struct subtype
{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	typedef decltype(*std::declval<_T>()) type;
#else
	typedef BOOST_TYPEOF(*declval<_T>()) type;
#endif
};

#if 0
template <typename _T, std::size_t _N>
struct subtype<_T[_N]>
{
	typedef _T type;
};

template <typename _T>
struct subtype<_T*>
{
	typedef _T type;
};
#endif
}

#endif
