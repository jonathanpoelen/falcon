#ifndef _FALCON_ALGORITHM_DICHOTOMIC_ALGORITHM_HPP
#define _FALCON_ALGORITHM_DICHOTOMIC_ALGORITHM_HPP

#include <algorithm>

namespace falcon {

template<typename _RandomAccessIterator, typename _T, typename _Compare>
void __dichotomic_lower_bound_advance(_RandomAccessIterator& first, _RandomAccessIterator& last, const _T& val, _Compare& comp)
{
	typedef typename std::iterator_traits<_RandomAccessIterator>::difference_type
	_DistanceType;
	_DistanceType len = std::distance(first, last);

	if (len < 7 || !comp(*first, val))
		return ;

	_DistanceType patt = len/2;
	first += --patt;
	bool b = true;

	while (patt > 2)
	{
		b = comp(*first, val);
		if (b)
			first += patt;
		else
			first -= patt;
		patt /= 2;
	}
	if (b && !comp(*first, val))
		first -= patt * 2;
}

template<typename _T>
struct __algo_less
{
	template<typename _U>
	bool operator()(const _U& a, const _T& b) const
	{ return a < b; }
};

template<typename _RandomAccessIterator, typename _T>
void __dichotomic_lower_bound_advance(_RandomAccessIterator& first, _RandomAccessIterator& last, const _T& val)
{
	__algo_less<_T> comp;
	__dichotomic_lower_bound_advance(first, last, val, comp);
}


/**
 *  @brief Find the first occurrence of a value in a <em>sorted</em> sequence.
 *  @ingroup non_mutating_algorithms
 *  @param first An input iterator.
 *  @param last An input iterator.
 *  @param val The value to find.
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @c *i == @p val, or @p last if no such iterator exists.
 */
template<typename _RandomAccessIterator, typename _T>
_RandomAccessIterator dichotomic_find(_RandomAccessIterator first, _RandomAccessIterator last, const _T& val)
{
	__dichotomic_lower_bound_advance<>(first, last, val);
	return std::find<>(first, last, val);
}

/**
 *  @brief Find the first element in a <em>sorted</em> sequence for which a predicate is true.
 *  @ingroup non_mutating_algorithms
 *  @param first An input iterator.
 *  @param last An input iterator.
 *  @param pred A predicate.
 *  @param comp A functor to use for comparisons with @p dichotomic_lower_bound().
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @p pred(*i) is true, or @p last if no such iterator exists.
 */
template<typename _RandomAccessIterator, typename _T, typename _LowerCompare>
_RandomAccessIterator dichotomic_find(_RandomAccessIterator first, _RandomAccessIterator last, const _T& val, _LowerCompare lower_comp)
{
	__dichotomic_lower_bound_advance<>(first, last, val, lower_comp);
	return std::find<>(first, last, val);
}

/**
 *  @brief Find the first element in a <em>sorted</em> sequence for which a predicate is true.
 *  @ingroup non_mutating_algorithms
 *  @param first An input iterator.
 *  @param last An input iterator.
 *  @param pred A predicate.
 *  @param comp A functor to use for comparisons with @p dichotomic_lower_bound().
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @p pred(*i) is true, or @p last if no such iterator exists.
 */
template<typename _RandomAccessIterator, typename _T, typename _LowerCompare, typename _Predicate>
_RandomAccessIterator dichotomic_find_if(_RandomAccessIterator first, _RandomAccessIterator last, const _T& val, _LowerCompare lower_comp, _Predicate pred)
{
	__dichotomic_lower_bound_advance<>(first, last, val, lower_comp);
	return std::find_if<>(first, last, pred);
}


/**
 *  @brief Finds the first position in a <em>sorted</em> sequence in which @a val could be inserted without changing the ordering.
 *  @ingroup binary_search_algorithms
 *  @param  first   An iterator.
 *  @param  last    Another iterator.
 *  @param  val     The search term.
 *  @return An iterator pointing to the first element <em>not less
 *           than</em> @a val, or end() if every element is less
 *           than @a val.
 *
 *  The comparison function should have the same effects on ordering as
 *  the function used for the initial sort.
 */
template<typename _RandomAccessIterator, typename _T>
_RandomAccessIterator dichotomic_lower_bound(_RandomAccessIterator first, _RandomAccessIterator last, const _T& val)
{
	__dichotomic_lower_bound_advance<>(first, last, val);
	return std::lower_bound<>(first, last, val);
}

/**
 *  @brief Finds the first position in a <em>sorted</em> sequence in which @a val could be inserted without changing the ordering.
 *  @ingroup binary_search_algorithms
 *  @param  first   An iterator.
 *  @param  last    Another iterator.
 *  @param  val     The search term.
 *  @param  comp    A functor to use for comparisons.
 *  @return An iterator pointing to the first element <em>not less
 *           than</em> @a val, or end() if every element is less
 *           than @a val.
 *
 *  The comparison function should have the same effects on ordering as
 *  the function used for the initial sort.
 */
template<typename _RandomAccessIterator, typename _T, typename _Compare>
_RandomAccessIterator dichotomic_lower_bound(_RandomAccessIterator first, _RandomAccessIterator last, const _T& val, _Compare comp)
{
	__dichotomic_lower_bound_advance<>(first, last, val, comp);
	return std::lower_bound<>(first, last, val, comp);
}

}

#endif