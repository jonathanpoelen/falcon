#ifndef FALCON_CONTAINER_RANGE_CONTAINER_HPP
#define FALCON_CONTAINER_RANGE_CONTAINER_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/type_traits/is_same.hpp>
#include <falcon/container/range_access.hpp>
#include <falcon/iterator/iterator_category.hpp>

#include <iterator>
#include <algorithm>
#include <stdexcept>

namespace falcon {

/**
 * @brief Container between two iterators
 *
 * @ingroup sequences
 */
template<class Iterator>
class range_container
{
	typedef std::iterator_traits<Iterator> traits;
public:
	typedef typename traits::value_type value_type;
	typedef typename traits::pointer pointer;
	typedef typename traits::reference reference;
	typedef typename traits::difference_type difference_type;

	typedef std::size_t size_type;

	typedef Iterator iterator;

private:
	iterator first_;
	iterator last_;

public:
	CPP_CONSTEXPR range_container()
	: first_()
	, last_()
	{}

	CPP_CONSTEXPR range_container(iterator first, iterator last)
	: first_(first)
	, last_(last)
	{}

	range_container(iterator first, size_type n)
	: first_(first)
#if __cplusplus >= 201103L
	, last_(std::next(first, n))
#else
    , last_(first+n)
#endif
	{}

	CPP_CONSTEXPR range_container(const range_container& other)
	: first_(other.first_)
	, last_(other.last_)
	{}

	range_container& operator=(const range_container& other)
	{
		first_ = other.first_;
		last_ = other.last_;
	}

	void begin(pointer first)
	{ first_ = first; }

	void end(pointer last)
	{ last_ = last; }

	// Iterators.
  CPP_CONSTEXPR iterator begin() const
	{ return first_; }

  CPP_CONSTEXPR iterator end() const
	{ return last_; }

	// Capacity.
	CPP_CONSTEXPR size_type size() const
	{ return last_ - first_; }

	CPP_CONSTEXPR size_type max_size() const
	{ return size(); }

	CPP_CONSTEXPR bool empty() const
	{ return first_ == last_; }

	// Element access.
  CPP_CONSTEXPR reference operator[](size_type n) const
	{ return first_ + n; }

	CPP_CONSTEXPR reference at(size_type n) const
	{
		// Result of conditional expression must be an lvalue so use
		// boolean ? lvalue : (throw-expr, lvalue)
		return n < size() ? first_ + n
		: (std::out_of_range("range_container::at"), *first_);
	}

  CPP_CONSTEXPR reference front() const
	{ return *first_; }

  CPP_CONSTEXPR reference back() const
	{ return empty() ? *last_ : *(last_ - 1); }

	void swap(range_container& other)
	{
    using std::swap;
		swap(first_, other.first_);
		swap(last_, other.last_);
	}
};

/**
 * @brief  Range_container equality comparison.
 * @param  x  A %range_container.
 * @param  y  A %range_container of the same type as @a x.
 * @return  True iff the size and elements of the range_containers are equal.
 *
 * This is an equivalence relation.  It is linear in the size of the
 * range_containers. Range_containers are considered equivalent if their sizes are equal (if iterator is random_access_iterator_tag),
 * and if corresponding elements compare equal.
 */
template<class Iterator>
inline bool operator==(const range_container<Iterator>& x,
                       const range_container<Iterator>& y)
{
#if __cplusplus > 201103L
  return std::equal(x.begin(), x.end(), y.begin(), y.end());
#else
  typedef typename std::iterator_traits<Iterator>::iterator_category cat;
  if (is_same<cat, std::random_access_iterator_tag>::value)
  {
    if (std::distance(x.begin(), x.end()) != std::distance(y.begin(), y.end())) {
      return false;
    }
    return std::equal(x.begin(), x.end(), y.begin());
  }

  typedef typename range_container<Iterator>::iterator iterator;
  iterator first = x.begin();
  iterator last = x.end();
  iterator first2 = y.begin();
  iterator last2 = y.end();
  for (; first != last && first2 != last2; ++first, ++first2){
    if (!(*first == *first2)) {
      return false;
    }
  }
  return first == last && first2 == last2;
#endif
}

/**
 * @brief  Range_container ordering relation.
 * @param  x  A %range_container.
 * @param  y  A %range_container of the same type as @a x.
 * @return  True iff @a x is lexicographically less than @a y.
 *
 * This is a total ordering relation.  It is linear in the size of the
 * range_containers.  The elements must be comparable with @c <.
 *
 * See std::lexicographical_compare() for how the determination is made.
 */
template<class Iterator>
inline bool operator<(const range_container<Iterator>& x,
                      const range_container<Iterator>& y)
{ return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

/// Based on operator==
template<class Iterator>
inline bool operator!=(const range_container<Iterator>& x,
                       const range_container<Iterator>& y)
{ return !(x == y); }

/// Based on operator<
template<class Iterator>
inline bool operator>(const range_container<Iterator>& x,
                      const range_container<Iterator>& y)
{ return y < x; }

/// Based on operator<
template<class Iterator>
inline bool operator<=(const range_container<Iterator>& x,
                       const range_container<Iterator>& y)
{ return !(y < x); }

/// Based on operator<
template<class Iterator>
inline bool operator>=(const range_container<Iterator>& x,
                       const range_container<Iterator>& y)
{ return !(x < y); }

template<class Iterator>
range_container<Iterator> make_range_container(Iterator first, Iterator last)
{ return range_container<Iterator>(first, last); }

template<class Iterator>
range_container<Iterator> make_range_container(Iterator first, std::size_t n)
{ return range_container<Iterator>(first, n); }

template<class Container>
range_container<typename range_access_iterator<Container>::type>
make_range_container(Container& cont)
{
	return range_container<
		typename range_access_iterator<Container>::type
	>(begin(cont), end(cont));
}

template<class Container>
range_container<typename range_access_iterator<const Container>::type>
make_range_container(const Container& cont)
{
	return range_container<
		typename range_access_iterator<const Container>::type
	>(begin(cont), end(cont));
}

template<class Iterator>
range_container<Iterator>
seq(Iterator first, Iterator last)
{ return range_container<Iterator>(first, last); }

template<class Iterator>
range_container<Iterator>
seq(Iterator first, std::size_t n)
{ return range_container<Iterator>(first, n); }

namespace container {
  template<class Iterator>
  range_container<Iterator> range(Iterator first, Iterator last)
  { return make_range_container(first, last); }

  template<class Iterator>
  range_container<Iterator> range(Iterator first, std::size_t n)
  { return make_range_container(first, n); }

  template<class Container>
  range_container<typename range_access_iterator<Container>::type>
  range(Container& cont)
  { return make_range_container(cont); }

  template<class Container>
  range_container<typename range_access_iterator<const Container>::type>
  range(const Container& cont)
  { return make_range_container(cont); }
}

template<class Iterator>
void swap(range_container<Iterator>& x, range_container<Iterator> y)
{ x.swap(y); }

}

#endif
