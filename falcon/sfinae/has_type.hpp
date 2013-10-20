#ifndef FALCON_SFINAE_HAS_TYPE_HPP
#define FALCON_SFINAE_HAS_TYPE_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/yes_no_type.hpp>

#define __FALCON_HELPER_VALUE_TEST(_T)\
	public:\
		static const bool value = sizeof(test(static_cast<_T*>(0))) == sizeof(::falcon::yes_type);\
		typedef bool value_type;\
		typedef ::falcon::integral_constant<bool, value> type;

#if __cplusplus >= 201103L
#define FALCON_HELPER_VALUE_TEST(_T)\
	__FALCON_HELPER_VALUE_TEST(_T)\
	constexpr operator bool() { return value; }
#else
#define FALCON_HELPER_VALUE_TEST(_T) __FALCON_HELPER_VALUE_TEST(_T)
#endif

namespace falcon {
  namespace detail {
    template<class T, class R = void>
    struct enable_type
    { typedef R type; };

#if __cplusplus >= 201103L
    template<template<typename...>class T, class R = void>
    struct enable_template
    { typedef R type; };
#else
    template<template<typename>class T, class R = void>
    struct enable_template1
    { typedef R type; };

    template<template<typename,typename>class T, class R = void>
    struct enable_template2
    { typedef R type; };
#endif
  }
}

#define FALCON_CREATE_HAS_TYPE(_Name, _TypeName)\
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
  struct _Name : __falcon_##_Name##__has_type_test<Falcon_T>::type {}

#define FALCON_HAS_TYPE_NAME(_TypeName) has_##_TypeName

#define FALCON_CLASS_HAS_TYPE(_TypeName)\
	FALCON_CREATE_HAS_TYPE(has_##_TypeName, _TypeName)


#if __cplusplus >= 201103L
# define __FALCON_FALCON_CREATE_HAS_TEMPLATE_TYPE(_Name, _TypeName)\
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_template_type_test<Falcon_T\
  , typename ::falcon::detail::enable_template<Falcon_T::template xxx>::type>\
  : ::falcon::true_type {};
#else
# define __FALCON_FALCON_CREATE_HAS_TEMPLATE_TYPE(_Name, _TypeName)\
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_template_type_test<Falcon_T\
  , typename ::falcon::detail::enable_template<Falcon_T::template xxx>::type>\
  : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_template_type_test<Falcon_T\
  , typename ::falcon::detail::enable_template<Falcon_T::template xxx>::type>\
  : ::falcon::true_type {};
#endif

#define FALCON_CREATE_HAS_TEMPLATE_TYPE(_Name, _TypeName)\
	template<typename Falcon_T, class = void>\
	struct __falcon_##_Name##__has_template_type_test\
	: ::falcon::false_type {};\
  \
  __FALCON_FALCON_CREATE_HAS_TEMPLATE_TYPE(_Name, _TypeName)\
  \
  template<typename Falcon_T>\
  struct _Name : __falcon_##_Name##__has_template_type_test<Falcon_T>::type {}

#endif
