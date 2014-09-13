#ifndef FALCON_SFINAE_HAS_MEMBER_CALLABLE_HPP
#define FALCON_SFINAE_HAS_MEMBER_CALLABLE_HPP

#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/preprocessor/concat.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/config.hpp>

#include <type_traits>


namespace falcon { namespace sfinae { namespace aux_ {
template<class From, class To>
struct result_is_convertible : std::is_convertible<From, To> {};

template<class From>
struct result_is_convertible<From, void> : std::true_type {};
} } }

#define __FALCON_HAS_MEMBER_CALLABLE_TRAIT_NAMED_DEF_I(trait, name, callable)\
  template<class Falcon_T, class Signature, class Tpl, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::std::false_type {};\
  \
  template<class Falcon_T, class R, class... Args>\
  struct FALCON_CONCAT(trait,_impl)<\
    Falcon_T, R(Args...), ::falcon::parameter_pack<>,\
    typename ::std::enable_if<\
      ::falcon::sfinae::aux_::result_is_convertible<decltype(\
        callable name(std::declval<Args>()...)\
      ), R>::value\
    >::type\
  > : ::std::true_type {};\
  \
  template<class Falcon_T, class R, class... Args, class Tpl, class... TplArgs>\
  struct FALCON_CONCAT(trait,_impl)<\
    Falcon_T, R(Args...), ::falcon::parameter_pack<Tpl, TplArgs...>,\
    typename ::std::enable_if<\
      ::falcon::sfinae::aux_::result_is_convertible<decltype(\
        callable template name<Tpl, FALCON_IF_NOT_IN_IDE_PARSER(TplArgs)...>\
        (std::declval<Args>()...)\
      ), R>::value\
    >::type\
  > : ::std::true_type {};\
  \
  template<class Falcon_T, class Signature = void(), class... TplArgs FALCON_IF_IN_IDE_PARSER(=void)>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T, Signature, ::falcon::parameter_pack<TplArgs...>>::type {}


#define FALCON_HAS_MEMBER_CALLABLE_TRAIT_NAMED_DEF(trait, name)\
  __FALCON_HAS_MEMBER_CALLABLE_TRAIT_NAMED_DEF_I(\
    trait, name, std::declval<Falcon_T>().)

#define FALCON_HAS_STATIC_MEMBER_CALLABLE_TRAIT_NAMED_DEF(trait, name)\
  __FALCON_HAS_MEMBER_CALLABLE_TRAIT_NAMED_DEF_I(trait, name, Falcon_T::)


#define FALCON_HAS_MEMBER_TEMPLATE_TYPE_CALLABLE_TRAIT_NAMED_DEF(trait, name)\
  template<class Falcon_T, class Signature, class Tpl, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::std::false_type {};\
  \
  template<class Falcon_T, class R, class... Args, class Tpl, class... TplArgs>\
  struct FALCON_CONCAT(trait,_impl)<\
    Falcon_T, R(Args...), ::falcon::parameter_pack<Tpl, TplArgs...>,\
    typename ::std::enable_if<\
      ::falcon::sfinae::aux_::result_is_convertible<decltype(\
        typename ::falcon::use<\
          typename Falcon_T::template name<Tpl, TplArgs...>\
        >::type(std::declval<Args>()...)\
      ), R>::value\
    >::type\
  > : ::std::true_type {};\
  \
  template<class Falcon_T, class Signature = void, class... TplArgs FALCON_IF_IN_IDE_PARSER(=void)>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T, Signature, ::falcon::parameter_pack<TplArgs...>>::type {}


#define FALCON_HAS_MEMBER_CALLABLE_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_member_callable)

#define FALCON_HAS_MEMBER_CALLABLE_TRAIT_DEF(name)\
  FALCON_HAS_MEMBER_CALLABLE_TRAIT_NAMED_DEF(\
    FALCON_HAS_MEMBER_CALLABLE_NAME(name), name)


#define FALCON_HAS_STATIC_MEMBER_CALLABLE_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_static_member_callable)

#define FALCON_HAS_STATIC_MEMBER_CALLABLE_TRAIT_DEF(name)\
  FALCON_HAS_STATIC_MEMBER_CALLABLE_TRAIT_NAMED_DEF(\
    FALCON_HAS_STATIC_MEMBER_CALLABLE_NAME(name), name)


#define FALCON_HAS_MEMBER_TEMPLATE_TYPE_CALLABLE_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_member_template_type_callable)

#define FALCON_HAS_MEMBER_TEMPLATE_TYPE_CALLABLE_TRAIT_DEF(name)\
  FALCON_HAS_MEMBER_TEMPLATE_TYPE_CALLABLE_TRAIT_NAMED_DEF(\
    FALCON_HAS_MEMBER_TEMPLATE_TYPE_CALLABLE_NAME(name), name)

#endif
