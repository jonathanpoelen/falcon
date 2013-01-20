#ifndef FALCON_DELETE_ALL_HPP
#define FALCON_DELETE_ALL_HPP

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_pointer)
#include FALCON_BOOST_OR_STD_TRAITS(remove_reference)
#include <falcon/memory/destroy.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon
{

template<
	typename _Container,
	typename _T = typename FALCON_BOOST_OR_STD_NAMESPACE::remove_pointer<
		typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<
			typename range_access_subtype<_Container>::type
		>::type
	>::type
>
inline void delete_all(_Container& container)
{
	std::for_each<>(begin(container), end(container), default_delete_wrapper<_T>());
}

template<
	typename _ForwardIterator,
	typename _T = typename FALCON_BOOST_OR_STD_NAMESPACE::remove_pointer<
		typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<
			typename std::iterator_traits<_ForwardIterator>::value_type
		>::type
	>::type
>
inline void delete_all(_ForwardIterator first, _ForwardIterator last)
{
	std::for_each<>(first, last, default_delete_wrapper<_T>());
}

}

#endif