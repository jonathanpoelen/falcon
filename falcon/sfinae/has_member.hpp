#ifndef FALCON_SFINAE_HAS_MEMBER_HPP
#define FALCON_SFINAE_HAS_MEMBER_HPP

#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/type_traits/enable_type.hpp>
#include <falcon/preprocessor/concat.hpp>
#include <falcon/config.hpp>

#include <type_traits>


namespace falcon { namespace sfinae { namespace aux_ {
template<class, class Signature>
struct add_static_member_function_pointer
{ using type = Signature*; };

template<class, class Signature>
class add_member_function_pointer;

template<class T, class R, class... Args>
struct add_member_function_pointer<T, R(Args...)>
{ using type = R(T::*)(Args...); };

template<class T, class R, class... Args>
struct add_member_function_pointer<T, R(Args...) const>
{ using type = R(T::*)(Args...) const; };

template<class T, class R, class... Args>
struct add_member_function_pointer<T, R(Args...) volatile>
{ using type = R(T::*)(Args...) volatile; };

template<class T, class R, class... Args>
struct add_member_function_pointer<T, R(Args...) const volatile>
{ using type = R(T::*)(Args...) const volatile; };
} } }


#define FALCON_HAS_DATA_MEMBER_TRAIT_NAMED_DEF(trait, name)\
  template<class Falcon_T, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::std::false_type {};\
  \
  template<class Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::std::enable_if<(\
    !::std::is_function<decltype(Falcon_T::name)>::value\
  )>::type> : ::std::true_type {};\
  \
  template<class Falcon_T>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T>::type {}


#define FALCON_HAS_STATIC_DATA_MEMBER_TRAIT_NAMED_DEF(trait, name)\
  template<class Falcon_T, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::std::false_type {};\
  \
  template<class Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::std::enable_if<(\
    !::std::is_function<decltype(Falcon_T::name)>::value &&\
    !::std::is_member_object_pointer<decltype(&Falcon_T::name)>::value\
  )>::type> : ::std::true_type {};\
  \
  template<class Falcon_T>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T>::type {}


#define __FALCON_HAS_MEMBER_FUNCTION_TRAIT_NAMED_DEF_I(trait, name, mem_pointer, simple_test_type)\
  template<class Falcon_T, class Signature, class Tpl, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::std::false_type {};\
  \
  template<class Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T, void, ::falcon::parameter_pack<>\
  , typename ::std::enable_if<\
    simple_test_type ::value\
  >::type> : ::std::true_type {};\
  \
  template<class Falcon_T, class Signature>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T, Signature, ::falcon::parameter_pack<>\
  , typename ::falcon::enable_type<\
    decltype(static_cast<typename mem_pointer<Falcon_T, Signature>::type>(\
      &Falcon_T::xxx))\
  >::type> : ::std::true_type {};\
  \
  template<class Falcon_T, class Signature, class Tpl, class... TplArgs>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T, Signature\
  , ::falcon::parameter_pack<Tpl, TplArgs...>\
  , typename ::falcon::enable_type<\
    decltype(static_cast<typename mem_pointer<Falcon_T, Signature>::type>(\
      &Falcon_T::template xxx<Tpl, FALCON_IF_NOT_IN_IDE_PARSER(TplArgs)...>))\
  >::type> : ::std::true_type {};\
  \
  template<class Falcon_T, class Signature = void, class... TplArgs FALCON_IF_IN_IDE_PARSER(=void)>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T, Signature, ::falcon::parameter_pack<TplArgs...>>::type {}


#define FALCON_HAS_MEMBER_FUNCTION_TRAIT_NAMED_DEF(trait, name)\
  __FALCON_HAS_MEMBER_FUNCTION_TRAIT_NAMED_DEF_I(\
    trait, name, ::falcon::sfinae::aux_::add_member_function_pointer,\
    ::std::is_member_function_pointer<decltype(&Falcon_T::name)>)


#define FALCON_HAS_STATIC_MEMBER_FUNCTION_TRAIT_NAMED_DEF(trait, name)\
  __FALCON_HAS_MEMBER_FUNCTION_TRAIT_NAMED_DEF_I(\
    trait, name, ::falcon::sfinae::aux_::add_static_member_function_pointer,\
    ::std::is_function<decltype(Falcon_T::name)>)


#define FALCON_HAS_DATA_MEMBER_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_data_member)

#define FALCON_HAS_DATA_MEMBER_TRAIT_DEF(name)\
  FALCON_HAS_DATA_MEMBER_TRAIT_NAMED_DEF(\
    FALCON_HAS_DATA_MEMBER_NAME(name), name)


#define FALCON_HAS_STATIC_DATA_MEMBER_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_static_data_member)

#define FALCON_HAS_STATIC_DATA_MEMBER_TRAIT_DEF(name)\
  FALCON_HAS_STATIC_DATA_MEMBER_TRAIT_NAMED_DEF(\
    FALCON_HAS_STATIC_DATA_MEMBER_NAME(name), name)


#define FALCON_HAS_MEMBER_FUNCTION_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_member_function)

#define FALCON_HAS_MEMBER_FUNCTION_TRAIT_DEF(name)\
  FALCON_HAS_MEMBER_FUNCTION_TRAIT_NAMED_DEF(\
    FALCON_HAS_MEMBER_FUNCTION_NAME(name), name)


#define FALCON_HAS_STATIC_MEMBER_FUNCTION_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_static_member_function)

#define FALCON_HAS_STATIC_MEMBER_FUNCTION_TRAIT_DEF(name)\
  FALCON_HAS_STATIC_MEMBER_FUNCTION_TRAIT_NAMED_DEF(\
    FALCON_HAS_STATIC_MEMBER_FUNCTION_NAME(name), name)

#endif
