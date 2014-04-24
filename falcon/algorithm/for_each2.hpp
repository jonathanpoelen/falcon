#ifndef FALCON_ALGORITHM_FOR_EACH2_HPP
#define FALCON_ALGORITHM_FOR_EACH2_HPP

#include <falcon/utility/move.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/type_traits/enable_if.hpp>
#include <falcon/type_traits/disable_if.hpp>
#include <falcon/type_traits/is_iterator.hpp>
#include <falcon/c++/boost_or_std.hpp>

#include FALCON_BOOST_OR_STDTRAITS(remove_const)

namespace falcon {
namespace algorithm {

template <class ForwardIterator, class ForwardIterator2, class BinaryFunction>
typename enable_if_c<is_iterator<ForwardIterator2>, BinaryFunction>::type
for_each2(ForwardIterator first, ForwardIterator last,
					ForwardIterator2 first2, BinaryFunction func)
{
	for (; first != last; ++first, ++first2)
		func(*first, *first2);
	return FALCON_MOVE(func);
}

template <class ForwardIterator, class ForwardIterator2, class BinaryFunction>
BinaryFunction for_each2(ForwardIterator first, ForwardIterator last,
                         ForwardIterator2 first2, ForwardIterator2 last2,
                         BinaryFunction func)
{
	for (; first != last && first2 != last2; ++first, ++first2)
		func(*first, *first2);
	return FALCON_MOVE(func);
}

template <class Container, class Iterator, class BinaryFunction>
typename enable_if_c<is_iterator<Iterator>, BinaryFunction>::type
for_each2(Container& cont, Iterator first, BinaryFunction func)
{
	return for_each2(begin(cont), end(cont), first, func);
}

template <class Container, class Container2, class BinaryFunction>
typename disable_if_c<is_iterator<
	typename FALCON_BOOST_OR_STDNAMESPACE::remove_const<Container2>::type
>, BinaryFunction>::type
for_each2(Container& cont, Container2& cont2, BinaryFunction func)
{
	return for_each2(begin(cont), end(cont), begin(cont2), end(cont2), func);
}

template <class Container, class T, std::size_t N, class BinaryFunction>
BinaryFunction for_each2(Container& cont, T(&cont2)[N], BinaryFunction func)
{
	return for_each2(begin(cont), end(cont), &cont2[0], &cont2[N], func);
}

template <class ForwardIterator, class Container, class BinaryFunction>
typename disable_if_c<is_iterator<
	typename FALCON_BOOST_OR_STDNAMESPACE::remove_const<Container>::type
>, BinaryFunction>::type
for_each2(ForwardIterator first, ForwardIterator last,
					Container& cont, BinaryFunction func)
{
	return for_each2(first, last, begin(cont), end(cont), func);
}

template <class ForwardIterator, class T, std::size_t N, class BinaryFunction>
BinaryFunction for_each2(ForwardIterator first, ForwardIterator last,
                         T(&cont)[N], BinaryFunction func)
{
	return for_each2(first, last, &cont[0], &cont[N], func);
}

template <class Container, class ForwardIterator, class BinaryFunction>
BinaryFunction for_each2(Container& cont,
									 ForwardIterator first, ForwardIterator last, BinaryFunction func)
{
	return for_each2(begin(cont), end(cont), first, last, func);
}

}
}

#endif
