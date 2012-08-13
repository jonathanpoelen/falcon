#ifndef _FALCON_TYPE_TRAITS_IS_JAVA_ITERATOR_HPP
#define _FALCON_TYPE_TRAITS_IS_JAVA_ITERATOR_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {
template <typename _T>
struct is_java_iterator
: false_type
{};
}

#endif
