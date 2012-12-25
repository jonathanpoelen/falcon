#ifndef FALCON_TYPE_TRAITS_REMOVE_CONST_REFERENCE_HPP
#define FALCON_TYPE_TRAITS_REMOVE_CONST_REFERENCE_HPP

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_const)
#include FALCON_BOOST_OR_STD_TRAITS(remove_reference)

namespace falcon {
template<typename _T>
struct remove_const_reference
{
	typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_const<
		typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<_T>::type
	>::type type;
};

}

#endif