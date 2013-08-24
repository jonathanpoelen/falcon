#ifndef FALCON_TYPE_TRAITS_ADD_CONST_IF_REFERENCE_HPP
#define FALCON_TYPE_TRAITS_ADD_CONST_IF_REFERENCE_HPP

namespace falcon
{

template <typename T>
struct add_const_if_reference
{ typedef T type; };

template <typename T>
struct add_const_if_reference<T&>
{ typedef const T& type; };

}

#endif
