#ifndef FALCON_TYPE_TRAITS_USE_DEFAULT_HPP
#define FALCON_TYPE_TRAITS_USE_DEFAULT_HPP

namespace falcon{

struct use_default;

/**
 * Use _Default::type if the type of _T is use_default, otherwise use _T
 */
template<typename _T, typename _Default>
struct default_or_type
{ typedef _T type; };

template<typename _Default>
struct default_or_type<use_default, _Default>
{ typedef typename _Default::type type; };

}

#endif