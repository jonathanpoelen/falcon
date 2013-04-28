#ifndef FALCON_TYPE_TRAITS_IS_ITERATOR_HPP
#define FALCON_TYPE_TRAITS_IS_ITERATOR_HPP

#include <falcon/type_traits/has.hpp>
#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/c++/boost_or_std.hpp>
#if __cplusplus < 201103L
#include <boost/type_traits/is_pointer.hpp>
#endif

namespace falcon {

template<typename _T>
struct is_iterator
: falcon::integral_constant<bool,
	has_iterator_category<_T>::value
	|| FALCON_BOOST_OR_STD_NAMESPACE::is_pointer<_T>::value
> {};

template<typename _T, std::size_t _N>
struct is_iterator<_T[_N]>
: falcon::false_type
{};

}

#endif