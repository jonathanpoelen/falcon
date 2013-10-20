#ifndef FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP
#define FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP

#include <falcon/c++/boost_or_std.hpp>
#include <falcon/type_traits/yes_no_type.hpp>
#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/sfinae/detail/is_callable.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(is_class)


#define FALCON_HAS_ATTRIBUTE_TRAIT_NAMED_DEF(_Name, _AttrName)\
  template<typename Falcon_T, class = void>\
  struct __falcon_##_Name##__has_member_attribute_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_member_attribute_test<Falcon_T\
  , typename ::falcon::detail::enable_val<sizeof(Falcon_T::_AttrName)>::type>\
  : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct _Name : __falcon_##_Name##__has_member_attribute_test<Falcon_T>::type {}


#define FALCON_HAS_FUNCTION_TRAIT_NAMED_DEF(_Name, _FuncName)\
  template<typename Falcon_T, class = void, class = void>\
  struct __falcon_##_Name##__has_function_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_function_test<Falcon_T\
  , typename ::falcon::detail::enable_val<sizeof(&Falcon_T::_FuncName)>::type\
  , typename ::falcon::detail::enable_val<sizeof(Falcon_T::_FuncName)>::type\
  > : ::falcon::false_type {};\
  \
  template<typename Falcon_T, typename Falcon_U>\
  struct __falcon_##_Name##__has_function_test<Falcon_T\
  , typename ::falcon::detail::enable_val<sizeof(&Falcon_T::_FuncName)>::type\
  , Falcon_U> : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct _Name : __falcon_##_Name##__has_function_test<Falcon_T>::type {}


#define FALCON_HAS_MEMBER_FUNCTION_TRAIT_NAMED_DEF(_Name, _FuncName)\
  template<typename Falcon_T, class = void, class = void>\
  struct __falcon_##_Name##__has_memfunction_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_memfunction_test<Falcon_T\
  , typename ::falcon::detail::enable_val<sizeof(&Falcon_T::_FuncName)>::type\
  , typename ::falcon::detail::enable_val<sizeof(Falcon_T::_FuncName)>::type\
  > : ::falcon::false_type {};\
  \
  template<typename T, typename U>\
  struct __falcon_##_Name##__has_memfunction_test<T\
  , typename ::falcon::detail::enable_val<sizeof(&T::_FuncName)>::type , U>\
  {\
    template<typename R, typename TT>\
    static ::falcon::yes_type test(R TT::*);\
    static ::falcon::no_type test(...);\
    static const bool value = sizeof(test(&T::_FuncName)) == sizeof(::falcon::yes_type);\
  };\
  \
  template<typename Falcon_T>\
  struct _Name\
  : ::falcon::integral_constant<bool\
  , __falcon_##_Name##__has_memfunction_test<Falcon_T>::value\
  > {}


#define FALCON_HAS_STATIC_FUNCTION_TRAIT_NAMED_DEF(_Name, _FuncName)\
  template<typename Falcon_T, class = void, class = void>\
  struct __falcon_##_Name##__has_sfunction_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_sfunction_test<Falcon_T\
  , typename ::falcon::detail::enable_val<sizeof(&Falcon_T::_FuncName)>::type\
  , typename ::falcon::detail::enable_val<sizeof(Falcon_T::_FuncName)>::type\
  > : ::falcon::false_type {};\
  \
  template<typename T, typename U>\
  struct __falcon_##_Name##__has_sfunction_test<T\
  , typename ::falcon::detail::enable_val<sizeof(&T::_FuncName)>::type , U>\
  {\
    template<typename R, typename TT>\
    static ::falcon::yes_type test(R TT::*);\
    static ::falcon::no_type test(...);\
    static const bool value = sizeof(test(&T::_FuncName)) != sizeof(::falcon::yes_type);\
  };\
  \
  template<typename Falcon_T>\
  struct _Name\
  : ::falcon::integral_constant<bool\
  , __falcon_##_Name##__has_sfunction_test<Falcon_T>::value\
  > {}


#define FALCON_HAS_MEMBER_TRAIT_NAMED_DEF(_Name, _FuncName)\
	template <typename Falcon_T\
	, bool = FALCON_BOOST_OR_STD_NAMESPACE::is_class<Falcon_T>::value>\
	struct __falcon_##_Name##__has_member_test\
	{\
    template<typename U, U>\
    struct helper{};\
		struct base { void _FuncName(); };\
		struct derived : public Falcon_T, public base {};\
		\
		template <typename U>\
		static ::falcon::no_type test(U*\
		, helper<void(base::*)(), &U::_FuncName>* = 0);\
		static ::falcon::yes_type test(...);\
		\
		static const bool value = sizeof(test(static_cast<derived*>(0)))\
		== sizeof(::falcon::yes_type);\
	};\
  \
  template <typename Falcon_T>\
  struct __falcon_##_Name##__has_member_test<Falcon_T, false>\
  { static const bool value = false; };\
	\
	template <typename Falcon_T>\
	struct _Name\
	: ::falcon::integral_constant<bool\
	, __falcon_##_Name##__has_member_test<Falcon_T>::value\
	> {}


# define FALCON_HAS_SIGNATURE_TRAIT_NAMED_DEF(_Name, _FuncName)\
  template<typename Falcon_T, typename Signature, class = void>\
  struct __falcon_##_Name##__has_signature_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T, typename Signature>\
  struct __falcon_##_Name##__has_signature_test<Falcon_T, Signature\
  , typename ::falcon::detail::enable_val<\
    sizeof(static_cast<Signature>(&Falcon_T::_FuncName))>::type\
  > : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Signature>\
  struct _Name : __falcon_##_Name##__has_signature_test<Falcon_T, Signature>::type {};


#define FALCON_HAS_ATTRIBUTE_TRAIT_DEF(_AttrName)\
  FALCON_HAS_ATTRIBUTE_TRAIT_NAMED_DEF(has_##_AttrName##_attribute, _AttrName)

#define FALCON_HAS_FUNCTION_TRAIT_DEF(_FuncName)\
  FALCON_HAS_FUNCTION_TRAIT_NAMED_DEF(has_##_FuncName##_function, _FuncName)

#define FALCON_HAS_MEMBER_FUNCTION_TRAIT_DEF(_FuncName)\
  FALCON_HAS_MEMBER_FUNCTION_TRAIT_NAMED_DEF(has_##_FuncName##_member_function\
  , _FuncName)

#define FALCON_HAS_STATIC_FUNCTION_TRAIT_DEF(_FuncName)\
  FALCON_HAS_STATIC_FUNCTION_TRAIT_NAMED_DEF(has_##_FuncName##_static_function\
  , _FuncName)

#define FALCON_HAS_MEMBER_TRAIT_DEF(_Name)\
  FALCON_HAS_MEMBER_TRAIT_NAMED_DEF(has_##_Name##_member, _Name)

#define FALCON_HAS_SIGNATURE_TRAIT_DEF(_Name)\
  FALCON_HAS_SIGNATURE_TRAIT_NAMED_DEF(has_##_Name##_signature, _Name)

#endif
