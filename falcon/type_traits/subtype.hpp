#ifndef _FALCON_TYPE_TRAITS_SUBTYPE_HPP
#define _FALCON_TYPE_TRAITS_SUBTYPE_HPP

#if __cplusplus >= 201103L
# include <utility>
#else
# include <falcon/utility/declval.hpp>
# include <boost/typeof/typeof.hpp>
#endif

namespace falcon {
template <typename T>
struct subtype
{
#if __cplusplus >= 201103L
	typedef decltype(*std::declval<T>()) type;
#else
	typedef BOOSTTYPEOF(*declval<T>()) type;
#endif
};

#if 0
template <typename T, std::size_t _N>
struct subtype<T[_N]>
{
	typedef T type;
};

template <typename T>
struct subtype<T*>
{
	typedef T type;
};
#endif
}

#endif
