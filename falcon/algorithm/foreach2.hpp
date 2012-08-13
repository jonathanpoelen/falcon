#ifndef _FALCON_ALGORITHM_FOREACH2_HPP
#define _FALCON_ALGORITHM_FOREACH2_HPP

#include <falcon/preprocessor/move.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {

template <typename _ForwardIterator, typename _ForwardIterator2, typename _Functor>
_Functor foreach2(_ForwardIterator first, _ForwardIterator last,
				  _ForwardIterator2 first2, _Functor func)
{
	for (; first != last; ++first, ++first2)
		func(*first, *first2);
	return FALCON_MOVE(func);
}

template <typename _Container, typename _ForwardIterator, typename _Functor>
_Functor foreach2(_Container& cont,
				  _ForwardIterator first2, _Functor func)
{
	return foreach2<>(begin(cont), end(cont), first2, func);
}

template <typename _Container, typename _ForwardIterator, typename _Functor>
_Functor foreach2(const _Container& cont,
				  _ForwardIterator first2, _Functor func)
{
	return foreach2<>(begin(cont), end(cont), first2, func);
}

}

#endif