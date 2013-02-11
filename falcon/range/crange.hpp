#ifndef _FALCON_RANGE_CRANGE_HPP
#define _FALCON_RANGE_CRANGE_HPP

#include <falcon/iterator/fake_iterator.hpp>
#include <falcon/iterator/nexter_iterator.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/range/range.hpp>

namespace falcon {

template<typename _Iterator>
struct __crange_iterator
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
struct __crange_traits
: __crange_iterator<iterator::fake_iterator<
	_T,
	iterator::fake_iterator_less_comparison_tag
> >
{};

template<typename _T>
struct __reverse_crange_traits
: __crange_iterator<iterator::reverse_fake_iterator<
	_T,
	iterator::fake_iterator_less_comparison_tag
> >
{};

/**
 * \brief Create @c range used with for raw statement.
 *
 * @code
 * int main(){
 *   using falcon::crange;
 *   for (int n: crange(1,9))
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
inline /*constexpr*/ typename __crange_traits<int>::__range_type
crange(int first, int last)
{
	return {
		__crange_traits<int>::__iterator(first),
		__crange_traits<int>::__iterator(last)
	};
}

/**
 * \brief Create @ref range used with for raw statement.
 *
 * @code
 * int main(){
 *   using falcon::crange;
 *   for (int& n: crange(0,20,2))
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
inline /*constexpr*/ typename __crange_traits<int>::__step_range_type
crange(int first, int last, unsigned step)
{
	return {
		{__crange_traits<int>::__iterator(first), step},
		{__crange_traits<int>::__iterator(last), step}
	};
}


/**
 * \brief Create @c range used with for raw statement.
 *
 * @code
 * int main(){
 *   using falcon::rcrange;
 *   for (int n: rcrange(9,1))
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
inline /*constexpr*/ typename __reverse_crange_traits<int>::__range_type
rcrange(int first, int last)
{
	return {
		__reverse_crange_traits<int>::__iterator(first),
		__reverse_crange_traits<int>::__iterator(last)
	};
}

/**
 * \brief Create @ref range used with for raw statement.
 *
 * @code
 * int main(){
 *   using falcon::rcrange;
 *   for (int& n: rcrange(20,0,2))
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
inline /*constexpr*/ typename __reverse_crange_traits<int>::__step_range_type
rcrange(int first, int last, unsigned step)
{
	return {
		{__reverse_crange_traits<int>::__iterator(first), step},
		{__reverse_crange_traits<int>::__iterator(last), step}
	};
}


}

#endif