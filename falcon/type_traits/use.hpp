#ifndef FALCON_TYPE_TRAITS_USE_HPP
#define FALCON_TYPE_TRAITS_USE_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon{

struct use_default;

template<typename T>
struct is_default
: false_type
{};

template<>
struct is_default<use_default>
: true_type
{};

template <typename T>
struct use
{ typedef T type; };

template <typename T, typename Unless>
struct late_use
{ typedef T type; };

/**
 * Use Default::type if the type of T is use_default, otherwise use T
 */
template<typename Default, typename T>
struct default_or_type
{ typedef T type; };

template<typename Default>
struct default_or_type<Default, use_default>
{ typedef typename Default::type type; };

}

#endif
