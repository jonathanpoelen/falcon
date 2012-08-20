#ifndef FALCON_RANGE_RANGE_HPP
#define FALCON_RANGE_RANGE_HPP

#ifdef __GXX_EXPERIMENTAL_CXX0X__
# include <falcon/tuple/tuple_apply.hpp>
# include <falcon/utility/maker.hpp>
#endif
#include <utility> //std::swap, std::pair
#include <falcon/c++/constexpr.hpp>
#include <falcon/type_traits/ignore.hpp>
#include <falcon/type_traits/difference.hpp>
#include <falcon/type_traits/decay_and_strip.hpp>
#include <falcon/logical/range_comparisons.hpp>
#include <falcon/range/range_modifier.hpp>

namespace falcon {

template<typename _T>
struct range
{
	typedef _T value_type;
	typedef typename falcon::difference<_T>::type difference_type;

	_T left, right;

	CPP_CONSTEXPR range()
	: left()
	, right()
	{}

	CPP_CONSTEXPR range(const _T& __left, const _T& __right)
	: left(__left)
	, right(__right)
	{}

	CPP_CONSTEXPR range(const ignore_t&, const _T& __right)
	: left()
	, right(__right)
	{}

	CPP_CONSTEXPR range(const _T& __left, const ignore_t&)
	: left(__left)
	, right()
	{}

	template<typename _U>
	CPP_CONSTEXPR range(const range<_U>& other)
	: left(other.left)
	, right(other.right)
	{}

	range<_T>& operator=(const range<_T>& __r)
	{
		left = __r.left;
		right = __r.right;
		return *this;
	}

	template<class _U>
	range<_T>& operator=(const range<_U>& __r)
	{
		left = __r.left;
		right = __r.right;
		return *this;
	}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	constexpr range(const range<_T>&) = default;

	template<class _U, class _Enable = typename std::enable_if<
		std::is_convertible<_U, _T>::value>
	::type>
	constexpr range(_U&& __x, const _T& __y)
	: left(std::forward<_U>(__x))
	, right(__y)
	{}

	template<class _U, class _Enable = typename std::enable_if<
		std::is_convertible<_U, _T>::value>
	::type>
	constexpr range(const _T& __x, _U&& __y)
	: left(__x)
	, right(std::forward<_U>(__y))
	{}

	template<class _U1, class _U2, class _Enable = typename std::enable_if<
		std::is_convertible<_U1, _T>::value
		&& std::is_convertible<_U2, _T>::value
	>::type>
	constexpr range(_U1&& __x, _U2&& __y)
	: left(std::forward<_U1>(__x))
	, right(std::forward<_U2>(__y))
	{}

	template<class _U>
	constexpr range(range<_U>&& __r)
	: left(std::forward<_U>(__r.left))
	, right(std::forward<_U>(__r.right))
	{}

	template<class... _Args1, class... _Args2>
	constexpr range(std::piecewise_construct_t, std::tuple<_Args1...> __left, std::tuple<_Args2...> __right)
	: left(tuple_apply(__right, maker<_T>()))
	, right(tuple_apply(__left, maker<_T>()))
	{}

	range<_T>& operator=(range<_T>&& __r)
	{
		left = std::move(__r.left);
		right = std::move(__r.right);
		return *this;
	}

	template<class _U>
	range<_T>& operator=(range<_U>&& __r)
	{
		left = std::move(__r.left);
		right = std::move(__r.right);
		return *this;
	}
#endif

	/// Increase @p left and decrease @p right of @a n
	range<_T>& towards_infinity(const _T& n)
	{
		left -= n;
		right += n;
		return *this;
	}

	template<typename _U>
	range<_T>& towards_infinity(const _U& n)
	{
		left -= n;
		right += n;
		return *this;
	}

	/// Decrease @p left and increase @p right of @a n
	range<_T>& towards_reverse_infinity(const _T& n)
	{
		left += n;
		right -= n;
		return *this;
	}

	template<typename _U>
	range<_T>& towards_reverse_infinity(const _U& n)
	{
		left += n;
		right -= n;
		return *this;
	}

	/// Decrease @p left and @p right of @a n
	range<_T>& towards_left(const _T& n)
	{
		left -= n;
		right -= n;
		return *this;
	}

	template<typename _U>
	range<_T>& towards_left(const _U& n)
	{
		left -= n;
		right -= n;
		return *this;
	}

	/// Increase @p left and @p right of @a n
	range<_T>& towards_right(const _T& n)
	{
		left += n;
		right += n;
		return *this;
	}

	template<typename _U>
	range<_T>& towards_right(const _U& n)
	{
		left += n;
		right += n;
		return *this;
	}

	void reverse()
	{
		std::swap(left, right);
	}

	void swap(std::pair<_T, _T>& other)
	{
		using std::swap;
		swap(other.left, left);
		swap(other.right, right);
	}

	void swap(range<_T>& other)
	{
		using std::swap;
		swap(other.left, left);
		swap(other.right, right);
	}

	CPP_CONSTEXPR bool less_right() const
	{
		return left < right;
	}
	CPP_CONSTEXPR bool greater_right() const
	{
		return left > right;
	}
	CPP_CONSTEXPR bool equal_to_right() const
	{
		return left == right;
	}
	CPP_CONSTEXPR bool not_equal_to_right() const
	{
		return left != right;
	}
	CPP_CONSTEXPR bool less_equal_right() const
	{
		return left <= right;
	}
	CPP_CONSTEXPR bool greater_equal_right() const
	{
		return left >= right;
	}

	CPP_CONSTEXPR bool empty() const
	{
		return left == right;
	}

	CPP_CONSTEXPR bool has(const _T v) const
	{
		return left == v || right == v;
	}

	CPP_CONSTEXPR bool between(const _T v) const
	{
		return falcon::between<>(left, v, right);
	}
	CPP_CONSTEXPR bool inner(const _T v) const
	{
		return falcon::inner<>(left, v, right);
	}
	CPP_CONSTEXPR bool outside(const _T v) const
	{
		return falcon::outside<>(left, v, right);
	}
	CPP_CONSTEXPR bool inner_out(const _T v) const
	{
		return falcon::inner_out<>(left, v, right);
	}

	CPP_CONSTEXPR difference_type difference() const
	{
		return right - left;
	}

	range_modifier<range<_T> > modifier()
	{
		return range_modifier<range<_T> >(*this);
	}

	CPP_CONSTEXPR _T begin() const
	{
		return left;
	}

	CPP_CONSTEXPR _T end() const
	{
		return right;
	}

	CPP_CONSTEXPR std::pair<const _T&, const _T&> to_pair() const
	{
		return std::pair<const _T&, const _T&>(left, right);
	}
};


template<typename _T>
inline CPP_CONSTEXPR bool operator==(const range<_T>& __x, const range<_T>& __y)
{
	return __x.left == __y.left && __x.right == __y.right;
}

template<typename _T>
inline CPP_CONSTEXPR bool operator!=(const range<_T>& __x, const range<_T>& __y)
{
	return !(__x == __y);
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<class _T>
inline constexpr range<typename decay_and_strip<_T>::type>
make_range(_T&& __x, _T&& __y)
{
	typedef range<typename decay_and_strip<_T>::type> __range_type;
	return __range_type(std::forward<_T>(__x), std::forward<_T>(__y));
}
#else
template<class _T>
inline range<_T> make_ranger(_T __x, _T __y)
{ return range<_T>(__x, __y); }
#endif

template<typename _Iterator>
inline CPP_CONSTEXPR range<_Iterator> range_iterator(_Iterator left, _Iterator right)
{
	return range<_Iterator>(left, right);
}

template<typename _Container>
inline CPP_CONSTEXPR range<typename range_access_iterator<_Container>::type> range_iterator(_Container& container)
{
	typedef typename range_access_iterator<_Container>::type __type;
	return range<__type>(begin(container), end(container));
}

}

namespace std {

template<typename _T>
inline void swap(falcon::range<_T>& __x, falcon::range<_T>& __y)
{
	__x.swap(__y);
}
template<typename _T>
inline void swap(falcon::range<_T>& __x, pair<_T, _T>& __y)
{
	__x.swap(__y);
}
template<typename _T>
inline void swap(pair<_T, _T>& __x, falcon::range<_T>& __y)
{
	__y.swap(__x);
}

}

#endif
