#ifndef _FALCON_ALGORITHM_FOR_EACH2_HPP
#define _FALCON_ALGORITHM_FOR_EACH2_HPP

#include <falcon/preprocessor/move.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/type_traits/enable_if.hpp>
#include <falcon/type_traits/disable_if.hpp>
#include <falcon/type_traits/is_iterator.hpp>
#include <falcon/c++/boost_or_std.hpp>
#if __cplusplus <= 201100L
#include <boost/type_traits/remove_const.hpp>
#endif

namespace falcon {

template <typename _ForwardIterator, typename _ForwardIterator2, typename _Functor>
typename enable_if_c<is_iterator<_ForwardIterator2>, _Functor>::type
for_each2(_ForwardIterator first, _ForwardIterator last,
					_ForwardIterator2 first2, _Functor func)
{
	for (; first != last; ++first, ++first2)
		func(*first, *first2);
	return FALCON_MOVE(func);
}

template <typename _ForwardIterator, typename _ForwardIterator2, typename _Functor>
_Functor for_each2(_ForwardIterator first, _ForwardIterator last,
									 _ForwardIterator2 first2, _ForwardIterator2 last2, _Functor func)
{
	for (; first != last && first2 != last2; ++first, ++first2)
		func(*first, *first2);
	return FALCON_MOVE(func);
}

template <typename _Container, typename _Iterator, typename _Functor>
typename enable_if_c<is_iterator<_Iterator>, _Functor>::type
for_each2(_Container& cont, _Iterator first, _Functor func)
{
	return for_each2<>(begin(cont), end(cont), first, func);
}

template <typename _Container, typename _Container2, typename _Functor>
typename disable_if_c<is_iterator<
	typename FALCON_BOOST_OR_STD_NAMESPACE::remove_const<_Container2>::type
>, _Functor>::type
for_each2(_Container& cont, _Container2& cont2, _Functor func)
{
	return for_each2<>(begin(cont), end(cont), begin(cont2), end(cont2), func);
}

template <typename _Container, typename _T, std::size_t _N, typename _Functor>
_Functor for_each2(_Container& cont, _T(&cont2)[_N], _Functor func)
{
	return for_each2<>(begin(cont), end(cont), &cont2[0], &cont2[_N], func);
}

template <typename _ForwardIterator, typename _Container, typename _Functor>
typename disable_if_c<is_iterator<
	typename FALCON_BOOST_OR_STD_NAMESPACE::remove_const<_Container>::type
>, _Functor>::type
for_each2(_ForwardIterator first, _ForwardIterator last,
					_Container& cont, _Functor func)
{
	return for_each2<>(first, last, begin(cont), end(cont), func);
}

template <typename _ForwardIterator, typename _T, std::size_t _N, typename _Functor>
_Functor for_each2(_ForwardIterator first, _ForwardIterator last,
									 _T(&cont)[_N], _Functor func)
{
	return for_each2<>(first, last, &cont[0], &cont[_N], func);
}

template <typename _Container, typename _ForwardIterator, typename _Functor>
_Functor for_each2(_Container& cont,
									 _ForwardIterator first, _ForwardIterator last, _Functor func)
{
	return for_each2<>(begin(cont), end(cont), first, last, func);
}

}

#endif