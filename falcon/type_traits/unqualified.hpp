#ifndef _FALCON_TYPE_TRAITS_UNQUALIFIED_HPP
#define _FALCON_TYPE_TRAITS_UNQUALIFIED_HPP

#include <falcon/type_traits/remove_const_reference.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_volatile)

namespace falcon {
template<typename _T>
struct unqualified
{
	typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_volatile<
		typename remove_const_reference<_T>::type
	>::type type;
};
}

#endif
