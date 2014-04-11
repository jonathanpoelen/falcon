#ifndef FALCON_TYPE_TRAITS_DECAY_AND_STRIP_HPP
#define FALCON_TYPE_TRAITS_DECAY_AND_STRIP_HPP

#include <falcon/c++/boost_or_std.hpp>
#include <falcon/type_traits/strip_reference_wrapper.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(decay)

namespace falcon {

template<class T>
struct decay_and_strip
{
	typedef typename strip_reference_wrapper<
		typename FALCON_BOOST_OR_STD_NAMESPACE::decay<T>::type
	>::type type;
};

}

#endif
