#ifndef FALCON_MPL_TPL_HPP
#define FALCON_MPL_TPL_HPP

#include <falcon/mpl/arg.hpp>

namespace falcon {
namespace mpl {

template<template <class...> class T,
  std::size_t Start, std::size_t Stop, typename... Args>
struct __tpl
: __tpl<T, Start+1, Stop, Args..., arg<Start+1> >
{};

template<template <class...> class T,
  std::size_t Stop, typename... Args>
struct __tpl<T, Stop, Stop, Args...>
{ using type = T<Args...>; };

template<template <class...> class T>
struct __tpl_size
{ static const std::size_t value = -1u; };

template<template <class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 1; };

template<template <class, class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 2; };

template<template <class, class, class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 3; };

template<template <class, class, class, class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 4; };

template<template <class, class, class, class, class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 5; };

template<template <class, class, class, class, class, class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 6; };

template<template <class, class, class, class, class, class, class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 7; };

template<template <class, class, class, class, class, class, class, class>
  class T>
struct __tpl_size<T>
{ static const std::size_t value = 8; };

template<template<class, class, class, class, class, class, class, class,
  class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 9; };

template<template<class, class, class, class, class, class, class, class,
  class, class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 10; };

template<template<class, class, class, class, class, class, class, class,
  class, class, class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 11; };

template<template<class, class, class, class, class, class, class, class,
  class, class, class, class> class T>
struct __tpl_size<T>
{ static const std::size_t value = 12; };


template<template <class...> class T, std::size_t Start>
using tpl = typename __tpl<T, Start, Start + __tpl_size<T>::value>::type;

}
}

#endif
