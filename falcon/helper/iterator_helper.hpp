#ifndef _FALCON_HELPER_ITERATOR_HELPER_HPP
#define _FALCON_HELPER_ITERATOR_HELPER_HPP

#include <falcon/type_traits/has.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {
namespace helper {

template<typename _T>
struct is_iterator
: integral_constant<bool,
	has_difference_type<_T>::value &&
	has_iterator_category<_T>::value &&
	has_pointer<_T>::value &&
	has_reference<_T>::value &&
	has_value_type<_T>::value
> {};

}}

#endif
