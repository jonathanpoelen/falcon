#ifndef FALCON_CONTAINER_RANGE_CONTAINER_HPP
#define FALCON_CONTAINER_RANGE_CONTAINER_HPP

#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <falcon/container/range_access.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {

/**
 * @brief Container between two iterators
 *
 * @ingroup sequences
 */
template<typename _Iterator>
class range_container
{
	typedef std::iterator_traits<_Iterator> __traits;
public:
	typedef typename __traits::value_type value_type;
	typedef typename __traits::pointer pointer;
	typedef typename __traits::reference reference;
	typedef typename __traits::difference_type difference_type;

	typedef std::size_t size_type;

	typedef _Iterator iterator;

private:
	iterator _M_first;
	iterator _M_last;

public:
	CPP_CONSTEXPR range_container()
	: _M_first()
	, _M_last()
	{}

	CPP_CONSTEXPR range_container(iterator first, iterator last)
	: _M_first(first)
	, _M_last(last)
	{}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	range_container(iterator first, size_type n)
	: _M_first(first)
	, _M_last(std::next(first, n))
	{}
#endif

	CPP_CONSTEXPR range_container(const range_container& other)
	: _M_first(other._M_first)
	, _M_last(other._M_last)
	{}

	range_container& operator=(const range_container& other) CPP_NOEXCEPT
	{
		_M_first = other._M_first;
		_M_last = other._M_last;
	}

	void begin(pointer first) CPP_NOEXCEPT
	{ _M_first = first; }

	void end(pointer last) CPP_NOEXCEPT
	{ _M_last = last; }

	// Iterators.
	iterator begin() const CPP_NOEXCEPT
	{ return _M_first; }

	iterator end() const CPP_NOEXCEPT
	{ return _M_last; }

	// Capacity.
	CPP_CONSTEXPR size_type size() const CPP_NOEXCEPT
	{ return _M_last - _M_first; }

	CPP_CONSTEXPR size_type max_size() const CPP_NOEXCEPT
	{ return size(); }

	CPP_CONSTEXPR bool empty() const CPP_NOEXCEPT
	{ return _M_first == _M_last; }

	// Element access.
	reference operator[](size_type n) const
	{ return _M_first + n; }

	CPP_CONSTEXPR reference at(size_type n) const
	{
		// Result of conditional expression must be an lvalue so use
		// boolean ? lvalue : (throw-expr, lvalue)
		return n < size() ? _M_first + n
		: (std::out_of_range("range_container::at"), *_M_first);
	}

	reference front() const
	{ return *_M_first; }

	reference back() const
	{ return empty() ? *_M_last : *(_M_last - 1); }

	void swap(range_container& other) CPP_NOEXCEPT
	{
		std::swap<>(_M_first, other._M_first);
		std::swap<>(_M_last, other._M_last);
	}
};

template<typename _Iterator>
inline bool __dispath_equal(const range_container<_Iterator>& x,
														const range_container<_Iterator>& y,
														std::random_access_iterator_tag)
{ return (x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin())); }

template<typename _Iterator, typename _Tag>
inline bool __dispath_equal(const range_container<_Iterator>& x,
														const range_container<_Iterator>& y,
														_Tag)
{
	typedef typename range_container<_Iterator>::iterator iterator;
	iterator first = x.begin();
	iterator last = x.end();
	iterator first2 = y.begin();
	iterator last2 = y.end();
	for (; first != last && first2 != last2; ++first, ++first2){
		if (*first != *first2)
			return false;
	}
	return first == last && first2 == last2;
}

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
template<typename _Iterator>
inline bool operator==(const range_container<_Iterator>& x,
											 const range_container<_Iterator>& y)
{
	typedef typename std::iterator_traits<
		typename range_container<_Iterator>::iterator
	>::iterator_category __iterator_category;
	return __dispath_equal(x, y, __iterator_category());
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
template<typename _Iterator>
inline bool operator<(const range_container<_Iterator>& x,
											const range_container<_Iterator>& y)
{ return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

/// Based on operator==
template<typename _Iterator>
inline bool operator!=(const range_container<_Iterator>& x,
											 const range_container<_Iterator>& y)
{ return !(x == y); }

/// Based on operator<
template<typename _Iterator>
inline bool operator>(const range_container<_Iterator>& x,
											const range_container<_Iterator>& y)
{ return y < x; }

/// Based on operator<
template<typename _Iterator>
inline bool operator<=(const range_container<_Iterator>& x,
											 const range_container<_Iterator>& y)
{ return !(y < x); }

/// Based on operator<
template<typename _Iterator>
inline bool operator>=(const range_container<_Iterator>& x,
											 const range_container<_Iterator>& y)
{ return !(x < y); }

template<typename _Iterator>
range_container<_Iterator> make_range_container(_Iterator first, _Iterator last)
#ifdef __GXX_EXPERIMENTAL_CXX0X__
{ return {first, last}; }
#else
{ return range_container<_Iterator>(first, last); }
#endif

template<typename _Iterator>
range_container<_Iterator> make_range_container(_Iterator first, std::size_t n)
#ifdef __GXX_EXPERIMENTAL_CXX0X__
{ return {first, n}; }
#else
{ return range_container<_Iterator>(first, n); }
#endif

template<typename _Container>
range_container<typename range_access_iterator<_Container>::type>
make_range_container(_Container& cont)
#ifdef __GXX_EXPERIMENTAL_CXX0X__
{ return {begin(cont), end(cont)}; }
#else
{
	return range_container<
		typename range_access_iterator<_Container>::type
	>(begin(cont), end(cont));
}
#endif

template<typename _Container>
range_container<typename range_access_iterator<const _Container>::type>
make_range_container(const _Container& cont)
#ifdef __GXX_EXPERIMENTAL_CXX0X__
{ return {begin(cont), end(cont)}; }
#else
{
	return range_container<
		typename range_access_iterator<const _Container>::type
	>(begin(cont), end(cont));
}
#endif

}

namespace std {
	template<typename _Iterator>
	void swap(const falcon::range_container<_Iterator>& x,
						const falcon::range_container<_Iterator> y)
	{ x.swap(y); }
}

#endif