#ifndef FALCON_ALGORITHM_DICHOTOMOUS_HPP
#define FALCON_ALGORITHM_DICHOTOMOUS_HPP

#include <algorithm>

namespace falcon {

/**
 *  @brief Find the first occurrence of a value in a <em>sorted</em> sequence.
 *  @ingroup non_mutating_algorithms
 *  @param first An input iterator.
 *  @param last An input iterator.
 *  @param val The value to find.
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @c *i == @p val, or @p last if no such iterator exists.
 */
template<class RandomAccessIterator, class T>
RandomAccessIterator dichotomous_find(
  RandomAccessIterator first, RandomAccessIterator last
, const T& val)
{
  first = std::lower_bound(first, last, val);
  if (first != last && val < *first) {
    return last;
  }
	return first;
}

/**
 *  @brief Find the first element in a <em>sorted</em> sequence for which a predicate is true.
 *  @ingroup non_mutating_algorithms
 *  @param first An input iterator.
 *  @param last An input iterator.
 *  @param pred A predicate.
 *  @param lower_comp A functor to use for comparisons with @p std::lower_bound().
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @p pred(*i) is true, or @p last if no such iterator exists.
 */
template<class RandomAccessIterator, class T, class LowerCompare>
RandomAccessIterator dichotomous_find(
  RandomAccessIterator first, RandomAccessIterator last
, const T& val, LowerCompare lower_comp)
{
  first = std::lower_bound(first, last, val, lower_comp);
  if (first != last && lower_comp(val, *first)) {
    return last;
  }
  return first;
}

}

#endif
