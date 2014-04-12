#ifndef FALCON_TYPE_TRAITS_DEFAULT_OR_TYPE_HPP
#define FALCON_TYPE_TRAITS_DEFAULT_OR_TYPE_HPP

#include <falcon/type_traits/use_default.hpp>

namespace falcon{

/**
 * Use Default::type if the type of T is TypeIsDefault, otherwise use T
 */
template<typename Default, typename T, typename TypeIsDefault = use_default>
struct default_or_type
{ typedef T type; };

template<typename Default, typename TypeIsDefault>
struct default_or_type<Default, TypeIsDefault, TypeIsDefault>
{ typedef typename Default::type type; };

}

#endif
