#ifndef FALCON_SFINAE_MEMBER_IS_CALLABLE_HPP
#define FALCON_SFINAE_MEMBER_IS_CALLABLE_HPP

#include <falcon/sfinae/detail/is_callable.hpp>
#if __cplusplus >= 201103L
# include <falcon/parameter/parameter_pack.hpp>
# include <type_traits>
#else
# include <falcon/utility/declval.hpp>
#endif


#if __cplusplus >= 201103L

# define FALCON_CREATE_MEMBER_FUNCTION_IS_CALLABLE(_Name, _FuncName)\
  template<typename Falcon_T, typename, typename = void>\
  struct __falcon_##_Name##__is_callable_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T, typename... Falcon_Args>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T, ::falcon::parameter_pack<Falcon_Args...>\
  , typename ::falcon::detail::enable_val<\
    sizeof(::std::declval<Falcon_T>()._FuncName(::std::declval<Falcon_Args>()...),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename... Falcon_Args>\
  struct _Name : __falcon_##_Name##__is_callable_test<Falcon_T\
  , ::falcon::parameter_pack<Falcon_Args...>>::type {};


# define FALCON_CREATE_MEMBER_FUNCTION_IS_CALLABLE_AND_CONVERTIBLE(_Name, _FuncName)\
  template<typename Falcon_T, typename, typename, typename = void>\
  struct __falcon_##_Name##__is_callable_and_conv_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T, typename Falcon_Result, typename... Falcon_Args>\
  struct __falcon_##_Name##__is_callable_and_conv_test<Falcon_T, Falcon_Result\
  , ::falcon::parameter_pack<Falcon_Args...>\
  , typename ::falcon::detail::enable_val<\
    sizeof(returnval<Falcon_Result>(::std::declval<Falcon_T>()._FuncName(::std::declval<Args>()...)))\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename... Falcon_Args>\
  struct __falcon_##_Name##__is_callable_and_conv_test<Falcon_T, void\
  , ::falcon::parameter_pack<Falcon_Args...>\
  , typename ::falcon::detail::enable_val<\
    sizeof(::std::declval<Falcon_T>()._FuncName(::std::declval<Args>()...),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Falcon_Result, typename... Falcon_Args>\
  struct _Name : __falcon_##_Name##__is_callable_and_conv_test<Falcon_T, Falcon_Result\
  , ::falcon::parameter_pack<Falcon_Args...>>::type {};

#else

# define FALCON_CREATE_MEMBER_FUNCTION_IS_CALLABLE(_Name, _FuncName)\
  template<typename Falcon_T, typename, typename, typename = void>\
  struct __falcon_##_Name##__is_callable_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T\
  , ::falcon::detail::sfinae_unspecified, ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<sizeof(::falcon::declval<Falcon_T>()._FuncName(),0)>::type\
  > : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T, Falcon_U\
  , ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<\
    sizeof(::falcon::declval<Falcon_T>()._FuncName(::falcon::declval<Falcon_U>()),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Falcon_U, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T, Falcon_U, Falcon_U\
  , typename ::falcon::detail::enable_val<\
    sizeof(::falcon::declval<Falcon_T>()._FuncName(::falcon::declval<Falcon_U>()\
    , ::falcon::declval<Falcon_U>()),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T\
  , typename Falcon_U = ::falcon::detail::sfinae_unspecified\
  , typename Falcon_U = ::falcon::detail::sfinae_unspecified>\
  struct _Name : __falcon_##_Name##__is_callable_test<Falcon_T, Falcon_U, Falcon_U>::type {};


# define FALCON_CREATE_MEMBER_FUNCTION_IS_CALLABLE_AND_CONVERTIBLE(_Name, _FuncName)\
  template<typename Falcon_T, typename, typename, typename, typename = void>\
  struct __falcon_##_Name##__is_callable_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T, void\
  , ::falcon::detail::sfinae_unspecified, ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<sizeof(::falcon::declval<Falcon_T>()._FuncName(),0)>::type\
  > : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Falcon_Result>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T, Falcon_Result\
  , ::falcon::detail::sfinae_unspecified, ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<\
    sizeof(returnval<Falcon_Result>(::falcon::declval<Falcon_T>()._FuncName()))\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T, void, Falcon_U\
  , ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<\
    sizeof(::falcon::declval<Falcon_T>()._FuncName(::falcon::declval<Falcon_U>()),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Falcon_Result, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T, Falcon_Result, Falcon_U\
  , ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<\
    sizeof(returnval<Falcon_Result>(\
      ::falcon::declval<Falcon_T>()._FuncName(::falcon::declval<Falcon_U>())))\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Falcon_U, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T, void, Falcon_U, Falcon_U\
  , typename ::falcon::detail::enable_val<\
    sizeof(::falcon::declval<Falcon_T>()._FuncName(::falcon::declval<Falcon_U>()\
    , ::falcon::declval<Falcon_U>()),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Falcon_Result, typename Falcon_U, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_T, Falcon_Result, Falcon_U, Falcon_U\
  , typename ::falcon::detail::enable_val<\
    sizeof(returnval<Falcon_Result>(\
      ::falcon::declval<Falcon_T>()._FuncName(::falcon::declval<Falcon_U>()\
    , ::falcon::declval<Falcon_U>())))\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Falcon_Result\
  , typename Falcon_U = ::falcon::detail::sfinae_unspecified\
  , typename Falcon_U = ::falcon::detail::sfinae_unspecified>\
  struct _Name : __falcon_##_Name##__is_callable_test<Falcon_T\
  , Falcon_Result, Falcon_U, Falcon_U>::type {};

#endif


#define FALCON_CLASS_MEMBER_FUNCTION_IS_CALLABLE(_FuncName)\
  FALCON_CREATE_MEMBER_FUNCTION_IS_CALLABLE(_FuncName##_is_callable, _FuncName)

#define FALCON_CLASS_MEMBER_FUNCTION_IS_CALLABLE_AND_CONVERTIBLE(_FuncName)\
  FALCON_CREATE_MEMBER_FUNCTION_IS_CALLABLE_AND_CONVERTIBLE(\
    _FuncName##_member_is_callalable_and_convertible, _FuncName)

#endif
