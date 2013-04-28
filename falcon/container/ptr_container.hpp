#ifndef FALCON_CONTAINER_PTR_CONTAINER_HPP
#define FALCON_CONTAINER_PTR_CONTAINER_HPP

#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

namespace falcon {

/**
 * @brief Container between two pointers
 *
 * @ingroup sequences
 */
template<typename _T>
class ptr_container
{
public:
	typedef _T value_type;
	typedef _T* pointer;
	typedef const _T* const_pointer;
	typedef _T& reference;
	typedef const _T& const_reference;
	typedef std::ptrdiff_t difference_type;

	typedef std::size_t size_type;

	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

private:
	pointer _M_first;
	pointer _M_last;

public:
	CPP_CONSTEXPR ptr_container() CPP_NOEXCEPT
	: _M_first(0)
	, _M_last(0)
	{}

	CPP_CONSTEXPR ptr_container(pointer first, pointer last) CPP_NOEXCEPT
	: _M_first(first)
	, _M_last(last)
	{}

	CPP_CONSTEXPR ptr_container(pointer first, size_type n) CPP_NOEXCEPT
	: _M_first(first)
	, _M_last(first + n)
	{}

	CPP_CONSTEXPR ptr_container(const ptr_container& other) CPP_NOEXCEPT
	: _M_first(other._M_first)
	, _M_last(other._M_last)
	{}

	ptr_container& operator=(const ptr_container& other) CPP_NOEXCEPT
	{
		_M_first = other._M_first;
		_M_last = other._M_last;
	}

	void begin(pointer first) CPP_NOEXCEPT
	{ _M_first = first; }

	void end(pointer last) CPP_NOEXCEPT
	{ _M_last = last; }

	// Iterators.
	iterator begin() CPP_NOEXCEPT
	{ return iterator(_M_first); }

	const_iterator begin() const CPP_NOEXCEPT
	{ return const_iterator(_M_first); }

	iterator end() CPP_NOEXCEPT
	{ return iterator(_M_last); }

	const_iterator end() const CPP_NOEXCEPT
	{ return const_iterator(_M_last); }

	reverse_iterator rbegin() CPP_NOEXCEPT
	{ return reverse_iterator(end()); }

	const_reverse_iterator rbegin() const CPP_NOEXCEPT
	{ return const_reverse_iterator(end()); }

	reverse_iterator rend() CPP_NOEXCEPT
	{ return reverse_iterator(begin()); }

	const_reverse_iterator rend() const CPP_NOEXCEPT
	{ return const_reverse_iterator(begin()); }

#if __cplusplus >= 201103L
	const_iterator cbegin() const noexcept
	{ return const_iterator(_M_first); }

	const_iterator cend() const noexcept
	{ return const_iterator(_M_last); }

	const_reverse_iterator crbegin() const noexcept
	{ return const_reverse_iterator(end()); }

	const_reverse_iterator crend() const noexcept
	{ return const_reverse_iterator(begin()); }
#endif

	// Capacity.
	CPP_CONSTEXPR size_type size() const CPP_NOEXCEPT
	{ return _M_last - _M_first; }

	CPP_CONSTEXPR size_type max_size() const CPP_NOEXCEPT
	{ return size(); }

	CPP_CONSTEXPR bool empty() const CPP_NOEXCEPT
	{ return _M_first == _M_last; }

	// Element access.
	reference operator[](size_type n)
	{ return _M_first[n]; }

	CPP_CONSTEXPR const_reference operator[](size_type n) const CPP_NOEXCEPT
	{ return _M_first[n]; }

	reference at(size_type n)
	{
		if (n >= size())
			std::out_of_range("ptr_container::at");
		return _M_first[n];
	}

	CPP_CONSTEXPR const_reference at(size_type n) const
	{
		// Result of conditional expression must be an lvalue so use
		// boolean ? lvalue : (throw-expr, lvalue)
		return n < size() ? _M_first[n]
		: (std::out_of_range("ptr_container::at"), _M_first[0]);
	}

	reference front() CPP_NOEXCEPT
	{ return *_M_first; }

	const_reference front() const CPP_NOEXCEPT
	{ return *_M_first; }

	reference back() CPP_NOEXCEPT
	{ return empty() ? *_M_last : *(_M_last - 1); }

	const_reference back() const CPP_NOEXCEPT
	{ return empty() ? *_M_last : *(_M_last - 1); }

	void swap(ptr_container& other) CPP_NOEXCEPT
	{
		std::swap<>(_M_first, other._M_first);
		std::swap<>(_M_last, other._M_last);
	}
};

/**
 * @brief  Ptr_container equality comparison.
 * @param  x  A %ptr_container.
 * @param  y  A %ptr_container of the same type as @a x.
 * @return  True iff the size and elements of the ptr_containers are equal.
 *
 * This is an equivalence relation.  It is linear in the size of the
 * ptr_containers. Ptr_containers are considered equivalent if their sizes are equal,
 * and if corresponding elements compare equal.
 */
template<typename _Tp>
inline bool operator==(const ptr_container<_Tp>& x, const ptr_container<_Tp>& y)
{ return (x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin())); }

/**
 * @brief  Ptr_container ordering relation.
 * @param  x  A %ptr_container.
 * @param  y  A %ptr_container of the same type as @a x.
 * @return  True iff @a x is lexicographically less than @a y.
 *
 * This is a total ordering relation.  It is linear in the size of the
 * ptr_containers.  The elements must be comparable with @c <.
 *
 * See std::lexicographical_compare() for how the determination is made.
 */
template<typename _Tp>
inline bool operator<(const ptr_container<_Tp>& x, const ptr_container<_Tp>& y)
{ return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

/// Based on operator==
template<typename _Tp>
inline bool operator!=(const ptr_container<_Tp>& x, const ptr_container<_Tp>& y)
{ return !(x == y); }

/// Based on operator<
template<typename _Tp>
inline bool operator>(const ptr_container<_Tp>& x, const ptr_container<_Tp>& y)
{ return y < x; }

/// Based on operator<
template<typename _Tp>
inline bool operator<=(const ptr_container<_Tp>& x, const ptr_container<_Tp>& y)
{ return !(y < x); }

/// Based on operator<
template<typename _Tp>
inline bool operator>=(const ptr_container<_Tp>& x, const ptr_container<_Tp>& y)
{ return !(x < y); }

template<typename _T>
ptr_container<_T> make_ptr_container(_T * first, _T * last) CPP_NOEXCEPT
{ return ptr_container<_T>(first, last); }

template<typename _T>
ptr_container<_T> make_ptr_container(_T * first, std::size_t n) CPP_NOEXCEPT
{ return ptr_container<_T>(first, n); }

template<typename _T>
ptr_container<const _T> make_ptr_container(const _T * first, const _T * last) CPP_NOEXCEPT
{ return ptr_container<const _T>(first, last); }

template<typename _T>
ptr_container<const _T> make_ptr_container(const _T * first, std::size_t n) CPP_NOEXCEPT
{ return ptr_container<const _T>(first, n); }

template<typename _T, std::size_t _N>
ptr_container<_T> make_ptr_container(_T(&cont)[_N]) CPP_NOEXCEPT
{ return ptr_container<const _T>(&cont[0], &cont[_N]); }

template<typename _T, std::size_t _N>
ptr_container<const _T> make_ptr_container(const _T(&cont)[_N]) CPP_NOEXCEPT
{ return ptr_container<const _T>(&cont[0], &cont[_N]); }

}

namespace std {
	template<typename _T>
	void swap(const falcon::ptr_container<_T>& x, const falcon::ptr_container<_T> y) CPP_NOEXCEPT
	{ x.swap(y); }
}

#endif