#ifndef _FALCON_TYPE_TRAITS_DECAY_AND_STRIP_HPP
#define _FALCON_TYPE_TRAITS_DECAY_AND_STRIP_HPP

#include <type_traits>

namespace falcon {

// Helper which adds a reference to a type when given a reference_wrapper
template<typename _Tp>
struct __strip_reference_wrapper
{
	typedef _Tp __type;
};

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

template<typename _Tp>
struct decay_and_strip
{
	typedef typename __strip_reference_wrapper<
		typename std::decay<_Tp>::type
	>::__type type;
};

}

#endif