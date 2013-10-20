#ifndef FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP
#define FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP

#include <falcon/sfinae/sfinae.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/type_traits/yes_no_type.hpp>
#include <falcon/type_traits/integral_constant.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(is_class)

namespace falcon {
  namespace detail {
    template <bool, typename R = void>
    struct enable_val
    { typedef R type; };
  }
}

#define FALCON_CREATE_HAS_ATTRIBUTE(_Name, _AttrName)\
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


#define FALCON_CREATE_HAS_FUNCTION(_Name, _FuncName)\
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


#define FALCON_CREATE_HAS_MEMBER_FUNCTION(_Name, _FuncName)\
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
  , typename std::enable_val<sizeof(&T::_FuncName)>::type , U>\
  {\
    template<typename R, typename TT>\
    static ::falcon::sfinae_type::one test(R TT::*);\
    static ::falcon::sfinae_type::two test(...);\
    static const bool value = sizeof(test(&T::_FuncName)) == 1;\
  };\
  \
  template<typename Falcon_T>\
  struct _Name\
  : ::falcon::integral_constant<bool\
  , __falcon_##_Name##__has_memfunction_test<Falcon_T>::value\
  > {}


#define FALCON_CREATE_HAS_STATIC_FUNCTION(_Name, _FuncName)\
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
  , typename std::enable_val<sizeof(&T::_FuncName)>::type , U>\
  {\
    template<typename R, typename TT>\
    static ::falcon::sfinae_type::one test(R TT::*);\
    static ::falcon::sfinae_type::two test(...);\
    static const bool value = sizeof(test(&T::_FuncName)) != 1;\
  };\
  \
  template<typename Falcon_T>\
  struct _Name\
  : ::falcon::integral_constant<bool\
  , __falcon_##_Name##__has_sfunction_test<Falcon_T>::value\
  > {}


#define FALCON_CREATE_HAS_MEMBER(_Name, _FuncName)\
	template <typename Falcon_T,  bool = FALCON_BOOST_OR_STD_NAMESPACE::is_class<Falcon_T>::value>\
	class __falcon_##_Name##__has_member_test\
	{\
		struct base { void _FuncName(); };\
		struct derived : public Falcon_T, public base {};\
		\
		template <typename U>\
		static ::falcon::no_type test(U*, ::falcon::sfinae::helper<void(base::*)(), &U::_FuncName>* = 0);\
		static ::falcon::yes_type test(...);\
		\
		static const bool value = sizeof(test(static_cast<derived*>(0))) == sizeof(::falcon::yes_type);\
	};\
  \
  template <typename Falcon_T>\
  struct __falcon_##_Name##__has_member_test<Falcon_T, false>\
  { static const bool value = false; }\
	\
	template <typename Falcon_T>\
	struct _Name\
	: ::falcon::integral_constant<bool\
	, __falcon_##_Name##__has_member_test<Falcon_T>::value\
	> {}


# define FALCON_CREATE_HAS_SIGNATURE(_Name, _FuncName)\
  template<typename Falcon_T, typename Signature, class = void>\\
  struct __falcon_##_Name##__has_signature_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T, typename Signature>\
  struct __falcon_##_Name##__has_signature_test<Falcon_T, Signature\
  , typename ::falcon::detail::enable_val<sizeof(static_cast<Signature>(&Falcon_T::_FuncName))>::type\
  > : ::falcon::true_type {};\
  \
  template<typename Falcon_T, typename Signature>\
  struct _Name : __falcon_##_Name##__has_signature_test<Falcon_T, Signature>::type {};


#define FALCON_CLASS_HAS_ATTRIBUTE(_AttrName)\
  FALCON_CREATE_HAS_ATTRIBUTE(has_##_AttrName##_attribute, _AttrName)

#define FALCON_CLASS_HAS_FUNCTION(_FuncName)\
  FALCON_CREATE_HAS_FUNCTION(has_##_FuncName##_function, _FuncName)

#define FALCON_CLASS_HAS_MEMBER_FUNCTION(_FuncName)\
  FALCON_CREATE_HAS_MEMBER_FUNCTION(has_##_FuncName##_member_function, _FuncName)

#define FALCON_CLASS_HAS_STATIC_FUNCTION(_FuncName)\
  FALCON_CREATE_HAS_STATIC_FUNCTION(has_##_FuncName_static_function, _FuncName)

#define FALCON_CLASS_HAS_MEMBER(_Name)\
  FALCON_CREATE_HAS_MEMBER(has_##_Name##_member, _Name)

#define FALCON_CLASS_HAS_SIGNATURE(_Name)\
  FALCON_CREATE_HAS_SIGNATURE(has_##_Name##_signature, _Name)

#endif
