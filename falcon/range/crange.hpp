#ifndef _FALCON_RANGE_CRANGE_HPP
#define _FALCON_RANGE_CRANGE_HPP

#include <falcon/iterator/fake_iterator.hpp>
#include <falcon/iterator/nexter_iterator.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/range/range.hpp>

namespace falcon {

template<typename _T>
struct __crange_traits
{
	typedef falcon::iterator::fake_iterator<
		_T,
		falcon::iterator::fake_iterator_less_comparison_tag
	> __iterator;
	typedef falcon::range<__iterator> __range_type;

	typedef falcon::iterator::nexter_iterator<
		__iterator,
		falcon::placeholder_for_argument<
			1,
			falcon::plus_equal<__iterator, unsigned>,
			unsigned
		>
	> __step_iterator;
	typedef falcon::range<__step_iterator> __step_range_type;
};

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

}

#endif