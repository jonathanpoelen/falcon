#ifndef _FALCON_TYPE_TRAITS_UNQUALIFIED_HPP
#define _FALCON_TYPE_TRAITS_UNQUALIFIED_HPP

#include <type_traits>

namespace falcon {
template<typename _T>
struct unqualified
{
	typedef typename std::remove_volatile<
	typename std::remove_const<
			typename std::remove_reference<_T>::type
		>::type
	>::type type;
};
}

#endif
