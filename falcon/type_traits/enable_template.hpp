#ifndef FALCON_TYPE_TRAITS_ENABLE_TEMPLATE_HPP
#define FALCON_TYPE_TRAITS_ENABLE_TEMPLATE_HPP

namespace falcon {

#if __cplusplus >= 201103L
template<template<class...>class T, class R = void>
struct enable_template
{ typedef R type; };

template<template<class...>class T, class R = void>
using enable_template_t = typename enable_template<T, R>::type;
#endif

template<template<class>class T, class R = void>
struct enable_template1
{ typedef R type; };

template<template<class,class>class T, class R = void>
struct enable_template2
{ typedef R type; };

template<template<class,class,class>class T, class R = void>
struct enable_template3
{ typedef R type; };

template<template<class,class,class,class>class T, class R = void>
struct enable_template4
{ typedef R type; };

template<template<class,class,class,class,class>class T, class R = void>
struct enable_template5
{ typedef R type; };

template<template<class,class,class,class,class,class>class T, class R = void>
struct enable_template6
{ typedef R type; };


template<template<class>class T, class R = void>
using enable_template1_t = typename enable_template1<T, R>::type;

template<template<class, class>class T, class R = void>
using enable_template2_t = typename enable_template2<T, R>::type;

template<template<class,class,class>class T, class R = void>
using enable_template3_t = typename enable_template3<T, R>::type;

template<template<class,class,class,class>class T, class R = void>
using enable_template4_t = typename enable_template4<T, R>::type;

template<template<class,class,class,class,class>class T, class R = void>
using enable_template5_t = typename enable_template5<T, R>::type;

template<template<class,class,class,class,class,class>class T, class R = void>
using enable_template6_t = typename enable_template6<T, R>::type;

}

#endif
