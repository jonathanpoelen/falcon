#ifndef FALCON_DELETE_ALL_HPP
#define FALCON_DELETE_ALL_HPP

#ifndef __GXX_EXPERIMENTAL_CXX0X__
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#endif
#include <falcon/algorithm/algorithm.hpp>
#include <falcon/memory/destroy.hpp>
#include <falcon/type_traits/subtype.hpp>
#include <falcon/detail/dep_nspace.hpp>

namespace falcon
{

template<
	typename _Container,
	typename _T = typename _FALCON_DEP_NSPACE(remove_pointer)<
		typename _FALCON_DEP_NSPACE(remove_reference)<
			typename range_access_subtype<_Container>::type
		>::type
	>::type
>
inline void delete_all(_Container& container)
{
	algorithm::for_each<>(container, default_delete_wrapper<_T>());
}

template<
	typename _ForwardIterator,
	typename _T = typename _FALCON_DEP_NSPACE(remove_pointer)<
		typename _FALCON_DEP_NSPACE(remove_reference)<
			typename subtype<_ForwardIterator>::type
		>::type
	>::type
>
inline void delete_all(_ForwardIterator first, _ForwardIterator last)
{
	std::for_each<>(first, last, default_delete_wrapper<_T>());
}

}

#endif