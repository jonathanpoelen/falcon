#ifndef FALCON_ALGORITHM_DICHOTOMIC_ALGORITHM_HPP
#define FALCON_ALGORITHM_DICHOTOMIC_ALGORITHM_HPP

#include <algorithm>
#include <iterator>

namespace falcon {

template<typename T>
struct __algo_less
{
	template<typename U>
	bool operator()(const U& a, const T& b) const
	{ return a < b; }
};


/**
 *  @brief Finds the first position in a <em>sorted</em> sequence in which
 *          @a val could be inserted without changing the ordering.
 *  @ingroup binary_search_algorithms
 *  @param  first   An iterator.
 *  @param  last    Another iterator.
 *  @param  val     The search term.
 *  @param  comp    A functor to use for comparisons.
 *  @return An iterator pointing to the first element <em>not less
 *           than</em> @a val, or end() if every element is greater
 *           than @a val.
 *
 *  The comparison function should have the same effects on ordering as
 *  the function used for the initial sort.
 *
 *  <b>Complexity</b>: Logarithmic
 */
template<typename RandomAccessIterator, typename T, typename Compare>
RandomAccessIterator dichotomic_lower_bound(RandomAccessIterator first,
                                            RandomAccessIterator last,
                                            const T& val, Compare comp)
{
  typedef typename std::iterator_traits<RandomAccessIterator>
  ::difference_type difference_type;

  difference_type len = last - first;
  difference_type half;

  while (len > 0) {
    half = len >> 1;
    RandomAccessIterator middle = first + half;

    if (comp(*middle, val)) {
      first = middle;
      ++first;
      len = len - half - 1;
    }
    else {
      len = half;
    }
  }
  return first;
}

/**
 *  @brief Finds the first position in a <em>sorted</em> sequence in which
 *         @a val could be inserted without changing the ordering.
 *  @ingroup binary_search_algorithms
 *  @param  first   An iterator.
 *  @param  last    Another iterator.
 *  @param  val     The search term.
 *  @return An iterator pointing to the first element <em>not less
 *           than</em> @a val, or end() if every element is greater
 *           than @a val.
 *
 *  The comparison function should have the same effects on ordering as
 *  the function used for the initial sort.
 */
template<typename RandomAccessIterator, typename T>
RandomAccessIterator dichotomic_lower_bound(RandomAccessIterator first,
                                            RandomAccessIterator last, const T& val)
{
  return dichotomic_lower_bound(first, last, val, __algo_less<T>());
}


template<typename T>
struct __algo_greater
{
  template<typename U>
  bool operator()(const U& a, const T& b) const
  { return a > b; }
};

/**
 *  @brief Finds the last position in a <em>sorted</em> sequence in which
 *         @a val could be inserted without changing the ordering.
 *  @ingroup binary_search_algorithms
 *  @param  first   An iterator.
 *  @param  last    Another iterator.
 *  @param  val     The search term.
 *  @param  comp    A functor to use for comparisons.
 *  @return An iterator pointing to the first element <em>greater
 *           than</em> @a val, or end() if no elements are greater than @a val.
 *
 *  The comparison function should have the same effects on ordering as
 *  the function used for the initial sort.
 *
 *  <b>Complexity</b>: Logarithmic
 */
template<typename RandomAccessIterator, typename T, typename Compare>
RandomAccessIterator dichotomic_upper_bound(RandomAccessIterator first,
                                            RandomAccessIterator last,
                                            const T& val, Compare comp)
{
  typedef typename std::iterator_traits<RandomAccessIterator>
  ::difference_type difference_type;

  difference_type len = last - first;
  difference_type half;

  while (len > 0) {
    half = len >> 1;
    RandomAccessIterator middle = first + half;

    if (comp(val, *middle)) {
      len = half;
    }
    else{
      first = ++middle;
      len = len - half - 1;
    }
  }
  return first;
}

/**
 *  @brief Finds the last position in a <em>sorted</em> sequence in which
 *         @a val could be inserted without changing the ordering.
 *  @ingroup binary_search_algorithms
 *  @param  first   An iterator.
 *  @param  last    Another iterator.
 *  @param  val     The search term.
 *  @return An iterator pointing to the first element <em>greater
 *           than</em> @a val, or end() if no elements are greater than @a val.
 *
 *  The comparison function should have the same effects on ordering as
 *  the function used for the initial sort.
 *
 *  <b>Complexity</b>: Logarithmic
 */
template<typename RandomAccessIterator, typename T>
RandomAccessIterator dichotomic_upper_bound(RandomAccessIterator first,
                                            RandomAccessIterator last, const T& val)
{
  return dichotomic_upper_bound(first, last, val, __algo_greater<T>());
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
template<typename RandomAccessIterator, typename T>
RandomAccessIterator dichotomic_find(RandomAccessIterator first,
                                     RandomAccessIterator last, const T& val)
{
  first = dichotomic_lower_bound(first, last, val, __algo_less<T>());
  if (first != last && *first != val) {
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
 *  @param lower_comp A functor to use for comparisons with @p dichotomic_lower_bound().
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @p pred(*i) is true, or @p last if no such iterator exists.
 */
template<typename RandomAccessIterator, typename T, typename LowerCompare>
RandomAccessIterator dichotomic_find(RandomAccessIterator first,
                                     RandomAccessIterator last, const T& val,
                                     LowerCompare lower_comp)
{
  first = dichotomic_lower_bound(first, last, val, lower_comp);
  if (first != last && *first != val) {
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
 *  @param lower_comp A functor to use for comparisons with @p dichotomic_lower_bound().
 *  @return The first iterator @c i in the range @p [first,last)
 *  such that @p pred(*i) is true, or @p last if no such iterator exists.
 */
template<typename RandomAccessIterator, typename T, typename LowerCompare, typename Predicate>
RandomAccessIterator dichotomic_find_if(RandomAccessIterator first,
                                        RandomAccessIterator last, const T& val,
                                        LowerCompare lower_comp, Predicate pred)
{
  first = dichotomic_lower_bound(first, last, val, lower_comp);
  if (first != last && !pred(*first, val)) {
    return last;
  }
  return first;
}

}

#endif
