#ifndef _FALCON_TYPE_TRAITS_DIFFERENCE_HPP
#define _FALCON_TYPE_TRAITS_DIFFERENCE_HPP

#if __cplusplus > 201100L
# include <type_traits>
namespace falcon {
template <typename _T>
struct difference
{
	typedef decltype(std::declval<_T>() - std::declval<_T>()) type;
};
}
#else
# include <cstddef>
# include <boost/type_traits/remove_cv.hpp
# include <falcon/type_traits/use_if.hpp>

namespace falcon {

template <typename _T>
struct difference
: use_if<
	use_difference_type<_T>,
	boost::remove_cv<_T>
>
{};

template <typename _T>
struct difference<_T*>
{
	typedef std::ptrdiff_t type;
};

}

#endif
#endif
