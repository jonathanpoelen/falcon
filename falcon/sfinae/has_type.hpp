#ifndef FALCON_SFINAE_HAS_TYPE_HPP
#define FALCON_SFINAE_HAS_TYPE_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/enable_template.hpp>
#include <falcon/type_traits/enable_type.hpp>
#include <falcon/preprocessor/concat.hpp>


#define FALCON_HAS_TYPE_TRAIT_NAMED_DEF(trait, name)\
  template<typename Falcon_T, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::falcon::enable_type<typename Falcon_T::name>::type>\
  : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T>::type {}


#if __cplusplus >= 201103L
# define FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF_S(trait, name)\
  template<typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::falcon::enable_template<Falcon_T::template name>::type>\
  : ::falcon::true_type {};
#else
# define FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF_S(trait, name)\
  template<typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::falcon::enable_template1<Falcon_T::template name>::type>\
  : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::falcon::enable_template2<Falcon_T::template name>::type>\
  : ::falcon::true_type {};
#endif

#define FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF(trait, name)\
	template<typename Falcon_T, class = void>\
	struct FALCON_CONCAT(trait,_impl)\
	: ::falcon::false_type {};\
  \
  FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF_S(trait, name)\
  \
  template<typename Falcon_T>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T>::type {}


#define FALCON_HAS_TYPE_NAME(name) FALCON_CONCAT(has_,name)

#define FALCON_HAS_TYPE_TRAIT_DEF(name)\
  FALCON_HAS_TYPE_TRAIT_NAMED_DEF(FALCON_HAS_TYPE_NAME(name), name)


#define FALCON_HAS_TEMPLATE_TYPE_NAME(name) FALCON_CONCAT(has_template_,name)

#define FALCON_HAS_TEMPLATE_TYPE_TRAIT_DEF(name)\
  FALCON_HAS_TEMPLATE_TYPE_TRAIT_NAMED_DEF(FALCON_HAS_TEMPLATE_TYPE_NAME(name), name)

#endif
