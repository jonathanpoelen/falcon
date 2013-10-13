#ifndef _FALCON_ALGORITHM_DICHOTOMIC_ALGORITHM_HPP
#define _FALCON_ALGORITHM_DICHOTOMIC_ALGORITHM_HPP

#include <algorithm>

namespace falcon {

template<typename RandomAccessIterator, typename T, typename Compare>
void __dichotomic_lower_bound_advance(RandomAccessIterator& first,
                                      RandomAccessIterator& last,
                                      const T& val, Compare comp)
{
	typedef typename std::iterator_traits<RandomAccessIterator>::difference_type
	DistanceType;
	DistanceType len = std::distance(first, last);

	if (len < 7 || !comp(*first, val))
		return ;

	DistanceType patt = len/2;
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

template<typename T>
struct __algo_less
{
	template<typename _U>
	bool operator()(const _U& a, const T& b) const
	{ return a < b; }
};


/**
 *  @brief Find the first occurrence of a value in a <em>sorted</em> sequence.
 *  @ingroup non_mutating_algorithms
 *  @param first An input iterator.
 *  @param last An input iterator.
 *  @param val The value to find.
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @c *i == @p val, or @p last if no such iterator exists.
 */
template<typename RandomAccessIterator, typename T>
RandomAccessIterator dichotomic_find(RandomAccessIterator first,
                                     RandomAccessIterator last, const T& val)
{
  __dichotomic_lower_bound_advance(first, last, val, __algo_less<T>());
	return std::find(first, last, val);
}

/**
 *  @brief Find the first element in a <em>sorted</em> sequence for which a predicate is true.
 *  @ingroup non_mutating_algorithms
 *  @param first An input iterator.
 *  @param last An input iterator.
 *  @param pred A predicate.
 *  @param lower_comp A functor to use for comparisons with @p dichotomic_lower_bound().
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @p pred(*i) is true, or @p last if no such iterator exists.
 */
template<typename RandomAccessIterator, typename T, typename LowerCompare>
RandomAccessIterator dichotomic_find(RandomAccessIterator first,
                                     RandomAccessIterator last, const T& val,
                                     LowerCompare lower_comp)
{
	__dichotomic_lower_bound_advance(first, last, val, lower_comp);
	return std::find(first, last, val);
}

/**
 *  @brief Find the first element in a <em>sorted</em> sequence for which a predicate is true.
 *  @ingroup non_mutating_algorithms
 *  @param first An input iterator.
 *  @param last An input iterator.
 *  @param pred A predicate.
 *  @param lower_comp A functor to use for comparisons with @p dichotomic_lower_bound().
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @p pred(*i) is true, or @p last if no such iterator exists.
 */
template<typename RandomAccessIterator, typename T, typename LowerCompare, typename Predicate>
RandomAccessIterator dichotomic_find_if(RandomAccessIterator first,
                                        RandomAccessIterator last, const T& val,
                                        LowerCompare lower_comp, Predicate pred)
{
	__dichotomic_lower_bound_advance(first, last, val, lower_comp);
	return std::find_if(first, last, pred);
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
template<typename RandomAccessIterator, typename T>
RandomAccessIterator dichotomic_lower_bound(RandomAccessIterator first,
                                            RandomAccessIterator last, const T& val)
{
  __dichotomic_lower_bound_advance(first, last, val, __algo_less<T>());
	return std::lower_bound(first, last, val);
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
template<typename RandomAccessIterator, typename T, typename Compare>
RandomAccessIterator dichotomic_lower_bound(RandomAccessIterator first,
                                            RandomAccessIterator last,
                                            const T& val, Compare comp)
{
	__dichotomic_lower_bound_advance(first, last, val, comp);
	return std::lower_bound(first, last, val, comp);
}

}

#endif
