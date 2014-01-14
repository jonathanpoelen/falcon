#ifndef FALCON_TYPE_TRAITS_IS_ITERATOR_HPP
#define FALCON_TYPE_TRAITS_IS_ITERATOR_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/helper/has_iterator_category.hpp>
#include <falcon/c++/boost_or_std.hpp>
#if __cplusplus < 201103L
#include <boost/type_traits/is_pointer.hpp>
#endif

namespace falcon {

template<typename T>
struct is_iterator
: falcon::integral_constant<bool,
	has_iterator_category<T>::value
	|| FALCON_BOOST_OR_STD_NAMESPACE::is_pointer<T>::value
> {};

template<typename T, std::size_t N>
struct is_iterator<T[N]>
: falcon::false_type
{};

}

#endif
