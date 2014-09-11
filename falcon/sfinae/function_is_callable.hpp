#ifndef FALCON_SFINAE_FUNCTION_IS_CALLABLE_HPP
#define FALCON_SFINAE_FUNCTION_IS_CALLABLE_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/enable_type.hpp>
#include <falcon/sfinae/detail/is_callable.hpp>
#if __cplusplus >= 201103L
# include <falcon/parameter/parameter_pack.hpp>
# include <type_traits>
#else
# include <falcon/utility/declval.hpp>
#endif


#if __cplusplus >= 201103L

# define FALCON_FUNCTION_IS_CALLABLE_TRAIT_NAMED_DEF(_Name, _FuncName)\
  template<typename, typename = void>\
  struct __falcon_##_Name##__is_callable_test\
  : ::falcon::false_type {};\
  \
  template<typename... Falcon_Args>\
  struct __falcon_##_Name##__is_callable_test<::falcon::parameter_pack<Falcon_Args...>\
  , typename ::falcon::enable_type<\
    decltype(_FuncName(::std::declval<Falcon_Args>()...))\
  >::type> : ::falcon::true_type {};\
  \
  template<typename... Falcon_Args>\
  struct _Name : __falcon_##_Name##__is_callable_test<\
    ::falcon::parameter_pack<Falcon_Args...>> {};


# define FALCON_FUNCTION_IS_CALLABLE_AND_CONVERTIBLE_TRAIT_NAMED_DEF(_Name, _FuncName)\
  template<typename, typename, typename = void>\
  struct __falcon_##_Name##__is_callable_and_conv_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_Result, typename... Falcon_Args>\
  struct __falcon_##_Name##__is_callable_and_conv_test<Falcon_Result\
  , ::falcon::parameter_pack<Falcon_Args...>\
  , typename ::std::enable_if<\
    std::is_convertible<\
      decltype(_FuncName(::std::declval<Falcon_Args>()...)), Falcon_Result\
    >::value\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_Result, typename... Falcon_Args>\
  struct _Name : __falcon_##_Name##__is_callable_and_conv_test<Falcon_Result\
  , ::falcon::parameter_pack<Falcon_Args...>>::type {};

#else

# define FALCON_FUNCTION_IS_CALLABLE_TRAIT_NAMED_DEF(_Name, _FuncName)\
  template<typename, typename, typename = void>\
  struct __falcon_##_Name##__is_callable_test\
  : ::falcon::false_type {};\
  \
  template<>\
  struct __falcon_##_Name##__is_callable_test<\
    ::falcon::detail::sfinae_unspecified, ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<sizeof(_FuncName(),0)>::type\
  > : ::falcon::true_type {};\
  \
  template<typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_U\
  , ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<\
    sizeof(_FuncName(::falcon::declval<Falcon_U>()),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_U, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_U, Falcon_U\
  , typename ::falcon::detail::enable_val<\
    sizeof(_FuncName(::falcon::declval<Falcon_U>()\
    , ::falcon::declval<Falcon_U>()),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<\
    typename Falcon_U = ::falcon::detail::sfinae_unspecified\
  , typename Falcon_U = ::falcon::detail::sfinae_unspecified>\
  struct _Name : __falcon_##_Name##__is_callable_test<Falcon_U, Falcon_U>::type {};


# define FALCON_FUNCTION_IS_CALLABLE_AND_CONVERTIBLE_TRAIT_NAMED_DEF(_Name, _FuncName)\
  template<typename, typename, typename, typename = void>\
  struct __falcon_##_Name##__is_callable_test\
  : ::falcon::false_type {};\
  \
  template<>\
  struct __falcon_##_Name##__is_callable_test<void\
  , ::falcon::detail::sfinae_unspecified, ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<sizeof(_FuncName(),0)>::type\
  > : ::falcon::true_type {};\
  \
  template<typename Falcon_Result>\
  struct __falcon_##_Name##__is_callable_test<Falcon_Result\
  , ::falcon::detail::sfinae_unspecified, ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<\
    sizeof(::falcon::detail::returnval<Falcon_Result>(_FuncName()))\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<void, Falcon_U\
  , ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<\
    sizeof(_FuncName(::falcon::declval<Falcon_U>()),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_Result, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_Result, Falcon_U\
  , ::falcon::detail::sfinae_unspecified\
  , typename ::falcon::detail::enable_val<\
    sizeof(::falcon::detail::returnval<Falcon_Result>(\
      _FuncName(::falcon::declval<Falcon_U>())))\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_U, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<void, Falcon_U, Falcon_U\
  , typename ::falcon::detail::enable_val<\
    sizeof(_FuncName(::falcon::declval<Falcon_U>()\
    , ::falcon::declval<Falcon_U>()),0)\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_Result, typename Falcon_U, typename Falcon_U>\
  struct __falcon_##_Name##__is_callable_test<Falcon_Result, Falcon_U, Falcon_U\
  , typename ::falcon::detail::enable_val<\
    sizeof(::falcon::detail::returnval<Falcon_Result>(\
      _FuncName(::falcon::declval<Falcon_U>()\
    , ::falcon::declval<Falcon_U>())))\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_Result\
  , typename Falcon_U = ::falcon::detail::sfinae_unspecified\
  , typename Falcon_U = ::falcon::detail::sfinae_unspecified>\
  struct _Name : __falcon_##_Name##__is_callable_test<\
    Falcon_Result, Falcon_U, Falcon_U>::type {};

#endif


#define FALCON_FUNCTION_IS_CALLABLE_TRAIT_DEF(_FuncName)\
  FALCON_FUNCTION_IS_CALLABLE_TRAIT_NAMED_DEF(_FuncName##_is_callable, _FuncName)

#define FALCON_FUNCTION_IS_CALLABLE_AND_CONVERTIBLE_TRAIT_DEF(_FuncName)\
  FALCON_FUNCTION_IS_CALLABLE_AND_CONVERTIBLE_TRAIT_NAMED_DEF(\
    _FuncName##_is_callable_and_convertible, _FuncName)

#endif
