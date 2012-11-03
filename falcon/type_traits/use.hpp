#ifndef FALCON_TYPE_TRAITS_USE_HPP
#define FALCON_TYPE_TRAITS_USE_HPP

namespace falcon{

struct use_default;

template <typename _T>
struct use
{ typedef _T type; };

template <typename _T, typename _Unless>
struct late_use
{ typedef _T type; };

/**
 * Use _Default::type if the type of _T is use_default, otherwise use _T
 */
template<typename _Default, typename _T>
struct default_or_type
{ typedef _T type; };

template<typename _Default>
struct default_or_type<_Default, use_default>
{ typedef typename _Default::type type; };

}

#endif