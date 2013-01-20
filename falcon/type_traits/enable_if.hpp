#ifndef _FALCON_TYPE_TRAITS_ENABLE_IF_HPP
#define _FALCON_TYPE_TRAITS_ENABLE_IF_HPP

# include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

// Define a nested type if some predicate holds.
template<bool, typename _Tp = void>
struct enable_if
{ typedef _Tp type; };

// Partial specialization for true.
template<typename _Tp>
struct enable_if<false, _Tp>
{};

template<class C, typename _Tp = void>
struct enable_if_c
: enable_if<C::value, _Tp>
{};

}

#endif