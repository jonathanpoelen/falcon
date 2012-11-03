#ifndef FALCON_TYPE_TRAITS_ADD_CONST_IF_REFERENCE_HPP
#define FALCON_TYPE_TRAITS_ADD_CONST_IF_REFERENCE_HPP

namespace falcon
{

template <typename _T>
struct add_const_if_reference
{ typedef _T type; };

template <typename _T>
struct add_const_if_reference<_T&>
{ typedef const _T& type; };

}

#endif