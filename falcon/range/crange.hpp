#ifndef _FALCON_RANGE_CRANGE_HPP
#define _FALCON_RANGE_CRANGE_HPP

#include <falcon/iterator/not_iterator.hpp>
#include <falcon/iterator/nexter_iterator.hpp>
#include <falcon/functional/operators.hpp>
#include <falcon/functional/placeholder_functor.hpp>
#include <falcon/range/range.hpp>

namespace falcon {

template<typename _T>
struct __crange_traits
{
	typedef falcon::iterator::not_iterator<
		_T,
		falcon::iterator::not_iterator_comparison_less_tag
	> __iterator_base;
	typedef falcon::range<__iterator_base> __type_range;

	typedef falcon::iterator::nexter_iterator<
		__iterator_base,
		falcon::placeholder_functor<
			1,
			falcon::plus_equal<__iterator_base, unsigned>,
			unsigned
		>
	> __iterator_step_base;
	typedef falcon::range<__iterator_step_base> __type_range_step;

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
inline constexpr typename __crange_traits<int>::__type_range
crange(int first, int last)
{
	return {{first}, {last}};
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
inline constexpr typename __crange_traits<int>::__type_range_step
crange(int first, int last, unsigned step)
{
	return {{first, step}, {last, step}};
}

}

#endif