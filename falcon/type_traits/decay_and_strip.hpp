#ifndef _FALCON_TYPE_TRAITS_DECAY_AND_STRIP_HPP
#define _FALCON_TYPE_TRAITS_DECAY_AND_STRIP_HPP

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(decay)

namespace boost {
	template<typename>
	class reference_wrapper;
}

namespace falcon {

// Helper which adds a reference to a type when given a reference_wrapper
template<typename _Tp>
struct __strip_reference_wrapper
{
	typedef _Tp __type;
};

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _Tp>
struct __strip_reference_wrapper<std::reference_wrapper<_Tp> >
{
	typedef _Tp& __type;
};

template<typename _Tp>
struct __strip_reference_wrapper<const std::reference_wrapper<_Tp> >
{
	typedef _Tp& __type;
};
#endif

template<typename _Tp>
struct __strip_reference_wrapper<boost::reference_wrapper<_Tp> >
{
	typedef _Tp& __type;
};

template<typename _Tp>
struct __strip_reference_wrapper<const boost::reference_wrapper<_Tp> >
{
	typedef _Tp& __type;
};

template<typename _Tp>
struct decay_and_strip
{
	typedef typename __strip_reference_wrapper<
		typename FALCON_BOOST_OR_STD_NAMESPACE::decay<_Tp>::type
	>::__type type;
};

}

#endif