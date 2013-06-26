#ifndef _FALCON_RANGE_CRANGE_HPP
#define _FALCON_RANGE_CRANGE_HPP

#include <falcon/iterator/integer_iterator.hpp>
#include <falcon/iterator/nexter_iterator.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/range/range.hpp>

namespace falcon {

template<typename _Iterator>
struct __integer_range_iterator
{
	typedef _Iterator __iterator;
	typedef range<_Iterator> __range_type;

	typedef iterator::nexter_iterator<
		_Iterator,
		placeholder_for_argument<
			1,
			plus_equal<_Iterator, unsigned>,
			unsigned
		>
	> __step_iterator;
	typedef range<__step_iterator> __step_range_type;
};

template<typename _T>
struct __integer_range_traits
: __integer_range_iterator<iterator::integer_iterator<
	_T,
	iterator::integer_iterator_less_comparison_tag
> >
{};

template<typename _T>
struct __reverse_integer_range_traits
: __integer_range_iterator<iterator::reverse_integer_iterator<
	_T,
	iterator::integer_iterator_less_comparison_tag
> >
{};

/**
 * \brief Create @c range used with for raw statement.
 *
 * @code
 * int main(){
 *   using falcon::integer_range;
 *   for (int n: integer_range(1,9))
 *     std::cout << n << ' ';
 * }
 * @endcode
 * is equivalent to
 * @code
 * int main(){
 *   for (int n = 1; n < 9; ++n)
 *     std::cout << n << ' ';
 * }
 * @endcode
 */
template<typename _T>
inline /*constexpr*/ typename __integer_range_traits<_T>::__range_type
integer_range(_T first, _T last)
{
	return {
		typename __integer_range_traits<_T>::__iterator(first),
		typename __integer_range_traits<_T>::__iterator(last)
	};
}

/**
 * \brief Create @ref range used with for raw statement.
 *
 * @code
 * int main(){
 *   using falcon::integer_range;
 *   for (int& n: integer_range(0,20,2))
 *     std::cout << ++n << ' ';
 * }
 * @endcode
 * is equivalent to
 * @code
 * int main(){
 *   for (int n = 0; n < 20; n += 2)
 *     std::cout << ++n << ' ';
 * }
 * @endcode
 */
template<typename _T>
inline /*constexpr*/ typename __integer_range_traits<_T>::__step_range_type
integer_range(_T first, _T last, unsigned step)
{
	return {
		{typename __integer_range_traits<_T>::__iterator(first), step},
		{typename __integer_range_traits<_T>::__iterator(last), step}
	};
}


/**
 * \brief Create @c range used with for raw statement.
 *
 * @code
 * int main(){
 *   using falcon::rinteger_range;
 *   for (int n: rinteger_range(9,1))
 *     std::cout << n << ' ';
 * }
 * @endcode
 * is equivalent to
 * @code
 * int main(){
 *   for (int n = 9; n > 1; --n)
 *     std::cout << n << ' ';
 * }
 * @endcode
 */
template<typename _T>
inline /*constexpr*/ typename __reverse_integer_range_traits<_T>::__range_type
reverse_integer_range(_T first, _T last)
{
	return {
		typename __reverse_integer_range_traits<_T>::__iterator(first),
		typename __reverse_integer_range_traits<_T>::__iterator(last)
	};
}

/**
 * \brief Create @ref range used with for raw statement.
 *
 * @code
 * int main(){
 *   using falcon::rinteger_range;
 *   for (int& n: rinteger_range(20,0,2))
 *     std::cout << --n << ' ';
 * }
 * @endcode
 * is equivalent to
 * @code
 * int main(){
 *   for (int n = 20; n > 0; n -= 2)
 *     std::cout << --n << ' ';
 * }
 * @endcode
 */
template<typename _T>
inline /*constexpr*/ typename __reverse_integer_range_traits<_T>::__step_range_type
reverse_integer_range(_T first, _T last, unsigned step)
{
	return {
		{typename __reverse_integer_range_traits<_T>::__iterator(first), step},
		{typename __reverse_integer_range_traits<_T>::__iterator(last), step}
	};
}

#define __FALCON_BUILD_INTEGER_RANGE(prefix, type, c)\
inline __##c##integer_range_traits<type>::__range_type \
prefix##range(type first, type last)\
{\
	return {\
		__##c##integer_range_traits<type>::__iterator(first),\
		__##c##integer_range_traits<type>::__iterator(last)\
	};\
}\
inline __##c##integer_range_traits<type>::__step_range_type \
prefix##range(type first, type last, unsigned step)\
{\
	return {\
		{__##c##integer_range_traits<type>::__iterator(first), step},\
		{__##c##integer_range_traits<type>::__iterator(last), step}\
	};\
}

#define FALCON_BUILD_INTEGER_RANGE(prefix, type)\
	__FALCON_BUILD_INTEGER_RANGE(prefix, type, )\
	__FALCON_BUILD_INTEGER_RANGE(reverse_##prefix, type, reverse_)

///integer_range<int>(first, last)
FALCON_BUILD_INTEGER_RANGE(i, int)
///integer_range<unsigned>(first, last)
FALCON_BUILD_INTEGER_RANGE(u, unsigned)
///integer_range<long>(first, last)
FALCON_BUILD_INTEGER_RANGE(l, long)
///integer_range<unsigned long>(first, last)
FALCON_BUILD_INTEGER_RANGE(ul, unsigned long)
///integer_range<long long>(first, last)
FALCON_BUILD_INTEGER_RANGE(ll, long long)
///integer_range<unsigned long long>(first, last)
FALCON_BUILD_INTEGER_RANGE(ull, unsigned long long)

#undef _FALCON_BUILD_INTEGER_RANGE
#undef FALCON_BUILD_INTEGER_RANGE

}

#endif
