#ifndef FALCON_TYPE_TRAITS_STATIC_CONST_HPP
#define FALCON_TYPE_TRAITS_STATIC_CONST_HPP

namespace falcon {

template<class T>
struct static_const
{ static constexpr T value{}; };

template<class T>
constexpr T static_const<T>::value;

}

#endif
