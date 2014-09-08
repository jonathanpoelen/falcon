#ifndef FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP
#define FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP

#include <falcon/c++/boost_or_std.hpp>
#include <falcon/type_traits/yes_no_type.hpp>
#include <falcon/type_traits/enable_type.hpp>
#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/preprocessor/concat.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(is_class)


#define FALCON_HAS_MEMBER_DATA_TRAIT_NAMED_DEF(trait, name)\
  template<typename Falcon_T, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::std::enable_if<(\
    !std::is_function<decltype(Falcon_T::name)>::value\
  )>::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T>::type {}


#define FALCON_HAS_FUNCTION_TRAIT_NAMED_DEF(trait, name)\
  template<typename Falcon_T, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::std::enable_if<\
    std::is_member_function_pointer<decltype(&Falcon_T::name)>::value\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::std::enable_if<\
    std::is_function<decltype(Falcon_T::name)>::value\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T>::type {}


#define FALCON_HAS_MEMBER_FUNCTION_TRAIT_NAMED_DEF(trait, name)\
  template<typename Falcon_T, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::std::enable_if<\
    std::is_member_function_pointer<decltype(&Falcon_T::name)>::value\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct trait\
  : ::falcon::integral_constant<bool\
  , FALCON_CONCAT(trait,_impl)<Falcon_T>::value\
  > {}


#define FALCON_HAS_STATIC_FUNCTION_TRAIT_NAMED_DEF(trait, name)\
  template<typename Falcon_T, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T\
  , typename ::std::enable_if<\
    std::is_function<decltype(Falcon_T::name)>::value\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct trait\
  : ::falcon::integral_constant<bool\
  , FALCON_CONCAT(trait,_impl)<Falcon_T>::value\
  > {}


#define FALCON_HAS_MEMBER_TRAIT_NAMED_DEF(trait, name)\
	template <typename Falcon_T\
	, bool = FALCON_BOOST_OR_STD_NAMESPACE::is_class<Falcon_T>::value>\
	struct FALCON_CONCAT(trait,_impl)\
	{\
    template<typename U, U>\
    struct helper{};\
		struct base { void name(); };\
		struct derived : public Falcon_T, public base {};\
		\
		template <typename U>\
		static ::falcon::no_type test(U*\
		, helper<void(base::*)(), &U::name>* = 0);\
		static ::falcon::yes_type test(...);\
		\
		static const bool value = sizeof(test(static_cast<derived*>(0)))\
		== sizeof(::falcon::yes_type);\
	};\
  \
  template <typename Falcon_T>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T, false>\
  { static const bool value = false; };\
	\
	template <typename Falcon_T>\
	struct trait\
	: ::falcon::integral_constant<bool\
	, FALCON_CONCAT(trait,_impl)<Falcon_T>::value\
	> {}


# define FALCON_HAS_SIGNATURE_TRAIT_NAMED_DEF(trait, name)\
  template<typename Falcon_T, typename Signature, class = void>\
  struct FALCON_CONCAT(trait,_impl)\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T, typename Signature>\
  struct FALCON_CONCAT(trait,_impl)<Falcon_T, Signature\
  , typename ::falcon::enable_type<\
    decltype(static_cast<Signature>(&Falcon_T::name))\
  >::type> : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Signature>\
  struct trait : FALCON_CONCAT(trait,_impl)<Falcon_T, Signature>::type {};


#define FALCON_HAS_MEMBER_DATA_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_attribute)

#define FALCON_HAS_MEMBER_DATA_TRAIT_DEF(name)\
  FALCON_HAS_MEMBER_DATA_TRAIT_NAMED_DEF(FALCON_HAS_MEMBER_DATA_NAME(name), name)


#define FALCON_HAS_FUNCTION_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_function)

#define FALCON_HAS_FUNCTION_TRAIT_DEF(name)\
  FALCON_HAS_FUNCTION_TRAIT_NAMED_DEF(FALCON_HAS_FUNCTION_NAME(name), name)


#define FALCON_HAS_MEMBER_FUNCTION_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_member_function)

#define FALCON_HAS_MEMBER_FUNCTION_TRAIT_DEF(name)\
  FALCON_HAS_MEMBER_FUNCTION_TRAIT_NAMED_DEF(FALCON_HAS_MEMBER_FUNCTION_NAME(name), name)


#define FALCON_HAS_STATIC_FUNCTION_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_static_function)

#define FALCON_HAS_STATIC_FUNCTION_TRAIT_DEF(name)\
  FALCON_HAS_STATIC_FUNCTION_TRAIT_NAMED_DEF(FALCON_HAS_STATIC_FUNCTION_NAME(name), name)


#define FALCON_HAS_MEMBER_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_member)

#define FALCON_HAS_MEMBER_TRAIT_DEF(name)\
  FALCON_HAS_MEMBER_TRAIT_NAMED_DEF(FALCON_HAS_MEMBER_NAME(name), name)


#define FALCON_HAS_SIGNATURE_NAME(name) \
  FALCON_CONCAT(FALCON_CONCAT(has_,name),_signature)

#define FALCON_HAS_SIGNATURE_TRAIT_DEF(name)\
  FALCON_HAS_SIGNATURE_TRAIT_NAMED_DEF(FALCON_HAS_SIGNATURE_NAME(name), name)

#endif
