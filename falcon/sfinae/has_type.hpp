#ifndef FALCON_SFINAE_HAS_TYPE_HPP
#define FALCON_SFINAE_HAS_TYPE_HPP

#include <falcon/type_traits/integral_constant.hpp>
namespace falcon {
  template<class T, class R = void>
  struct enable_type
  { typedef R type; };

#if __cplusplus >= 201103L
  template<template<typename...>class T, class R = void>
  struct enable_template
  { typedef R type; };

  template<class T, class R = void>
  using enable_type_t = typename enable_type<T, R>::type;

  template<template<typename...>class T, class R = void>
  using enable_template_t = typename enable_template<T, R>::type;

#else
  template<template<typename>class T, class R = void>
  struct enable_template1
  { typedef R type; };

  template<template<typename,typename>class T, class R = void>
  struct enable_template2
  { typedef R type; };
#endif
}

#define FALCON_HAS_TYPE_TRAIT_NAMED_DEF(_Name, _TypeName)\
  template<typename Falcon_T, class = void>\
  struct __falcon_##_Name##__has_type_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_type_test<Falcon_T\
  , typename ::falcon::enable_type<typename Falcon_T::_TypeName>::type>\
  : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct _Name : __falcon_##_Name##__has_type_test<Falcon_T>::type {\
    static const bool value = __falcon_##_Name##__has_type_test<Falcon_T>::value;\
  }

#define FALCON_HAS_TYPE_NAME(_TypeName) has_##_TypeName


#if __cplusplus >= 201103L
# define __FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF(_Name, _TypeName)\
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_template_type_test<Falcon_T\
  , typename ::falcon::enable_template<Falcon_T::template _TypeName>::type>\
  : ::falcon::true_type {};
#else
# define __FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF(_Name, _TypeName)\
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_template_type_test<Falcon_T\
  , typename ::falcon::enable_template<Falcon_T::template _TypeName>::type>\
  : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_template_type_test<Falcon_T\
  , typename ::falcon::enable_template<Falcon_T::template _TypeName>::type>\
  : ::falcon::true_type {};
#endif

#define FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF(_Name, _TypeName)\
	template<typename Falcon_T, class = void>\
	struct __falcon_##_Name##__has_template_type_test\
	: ::falcon::false_type {};\
  \
  __FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF(_Name, _TypeName)\
  \
  template<typename Falcon_T>\
  struct _Name : __falcon_##_Name##__has_template_type_test<Falcon_T>::type {\
    const static bool value = \
      __falcon_##_Name##__has_template_type_test<Falcon_T>::value;\
  }


#define FALCON_HAS_TYPE_TRAIT_DEF(_TypeName)\
  FALCON_HAS_TYPE_TRAIT_NAMED_DEF(has_##_TypeName, _TypeName)

#define FALCON_HAS_TEMPLATE_TYPE_TRAIT_DEF(_TypeName)\
  FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF(has_template_##_TypeName, _TypeName)

#endif
