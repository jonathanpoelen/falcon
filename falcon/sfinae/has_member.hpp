#ifndef FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP
#define FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP

#include <falcon/sfinae/sfinae.hpp>
#include <falcon/sfinae/has_type.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(is_class)

namespace facon {
  namespace detail {
    template <bool, typename R>
    struct enable_val
    { typedef R type; };
  }
}

#define FALCON_CREATE_HAS_MEMBER_ATTRIBUTE(_Name, _AttrName)\
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


#define FALCON_CREATE_HAS_FUNCTION(_Name, _AttrName)\
  template<typename Falcon_T, class = void, class = void>\
  struct __falcon_##_Name##__has_function_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_function_test<Falcon_T\
  , typename ::falcon::detail::enable_val<sizeof(&Falcon_T::_AttrName)>::type\
  , typename ::falcon::detail::enable_val<sizeof(Falcon_T::_AttrName)>::type\
  > : ::falcon::false_type {};\
  \
  template<typename Falcon_T, typename Falcon_U>\
  struct __falcon_##_Name##__has_function_test<Falcon_T\
  , typename ::falcon::detail::enable_val<sizeof(&Falcon_T::_AttrName)>::type\
  , Falcon_U> : ::falcon::true_type {};\
  \
  template<typename Falcon_T>\
  struct _Name : __falcon_##_Name##__has_function_test<Falcon_T>::type {}


#define FALCON_CREATE_HAS_MEMBER_FUNCTION(_Name, _AttrName)\
  template<typename Falcon_T, class = void, class = void>\
  struct __falcon_##_Name##__has_memfunction_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_memfunction_test<Falcon_T\
  , typename ::falcon::detail::enable_val<sizeof(&Falcon_T::_AttrName)>::type\
  , typename ::falcon::detail::enable_val<sizeof(Falcon_T::_AttrName)>::type\
  > : ::falcon::false_type {};\
  \
  template<typename T, typename U>\
  struct __falcon_##_Name##__has_memfunction_test<T\
  , typename std::enable_val<sizeof(&T::xxx)>::type , U>\
  {\
    template<typename R, typename TT>\
    static ::falcon::sfinae_type::one test(R TT::*);\
    static ::falcon::sfinae_type::two test(...);\
    static const bool value = sizeof(test(&T::xxx)) == 1;\
  };\
  \
  template<typename Falcon_T>\
  struct _Name \
  : ::falcon::integral_constant<bool\
  , __falcon_##_Name##__has_memfunction_test<Falcon_T>::value\
  > {}


#define FALCON_CREATE_HAS_STATIC_FUNCTION(_Name, _AttrName)\
  template<typename Falcon_T, class = void, class = void>\
  struct __falcon_##_Name##__has_sfunction_test\
  : ::falcon::false_type {};\
  \
  template<typename Falcon_T>\
  struct __falcon_##_Name##__has_sfunction_test<Falcon_T\
  , typename ::falcon::detail::enable_val<sizeof(&Falcon_T::_AttrName)>::type\
  , typename ::falcon::detail::enable_val<sizeof(Falcon_T::_AttrName)>::type\
  > : ::falcon::false_type {};\
  \
  template<typename T, typename U>\
  struct __falcon_##_Name##__has_sfunction_test<T\
  , typename std::enable_val<sizeof(&T::xxx)>::type , U>\
  {\
    template<typename R, typename TT>\
    static ::falcon::sfinae_type::one test(R TT::*);\
    static ::falcon::sfinae_type::two test(...);\
    static const bool value = sizeof(test(&T::xxx)) != 1;\
  };\
  \
  template<typename Falcon_T>\
  struct _Name \
  : ::falcon::integral_constant<bool\
  , __falcon_##_Name##__has_sfunction_test<Falcon_T>::value\
  > {}


#define FALCON_CREATE_HAS_MEMBER(_Name, _FuncName)\
	template <typename Falcon_T,  bool = FALCON_BOOST_OR_STD_NAMESPACE::is_class<Falcon_T>::value>\
	class _Name\
	{\
		struct base { void _FuncName(); };\
		struct derived : public Falcon_T, public base {};\
		\
		template <typename U>\
		static ::falcon::no_type test(U*, ::falcon::sfinae::helper<void(base::*)(), &U::_FuncName>* = 0);\
		static ::falcon::yes_type test(...);\
		\
		FALCON_HELPER_VALUE_TEST(derived);\
	};\
	template <typename Falcon_T>\
	struct _Name<Falcon_T, false>\
	{ static const bool value = false; }

#define FALCON_HAS_MEMBER_FUNCTION_NAME(_FuncName) has_member_function_##_FuncName

#define FALCON_CLASS_HAS_MEMBER_FUNCTION(_FuncName)\
	FALCON_CREATE_HAS_MEMBER_FUNCTION(FALCON_HAS_MEMBER_FUNCTION_NAME(_FuncName), _FuncName)


#define FALCON_CREATE_HAS_MEMBER_VAR(_Name, _VarName)\
	template <typename Falcon_T,  bool = FALCON_BOOST_OR_STD_NAMESPACE::is_class<Falcon_T>::value>\
	class _Name\
	{\
		template <typename U, typename V = decltype(U::_VarName)>\
		static ::falcon::yes_type test(U*);\
		static ::falcon::no_type test(...);\
		\
		FALCON_HELPER_VALUE_TEST(Falcon_T);\
	};\
	template <typename Falcon_T>\
	struct _Name<Falcon_T, false>\
	{ static const bool value = false; }

#define FALCON_HAS_MEMBER_VAR_NAME(_VarName) has_member_var_##_VarName

#define FALCON_CLASS_HAS_MEMBER_VAR(_VarName)\
	FALCON_CREATE_HAS_MEMBER_VAR(FALCON_HAS_MEMBER_VAR_NAME(_VarName), _VarName)

#if __cplusplus >= 201103L
# define FALCON_CREATE_HAS_SIGNATURE(_Name, _FuncName)\
	template <typename Falcon_T, typename _Signature>\
	class _Name;\
	\
	template <typename Falcon_T, typename _Functor, typename... _Args>\
	class _Name<Falcon_T, _Functor(_Args...)>\
	{\
		template <typename T, typename _Member>\
		struct impl\
		{\
			template <typename U> static ::falcon::yes_type test(U*, ::falcon::sfinae_type::helper<_Member, &U::_FuncName>* = 0);\
			static ::falcon::no_type test(...);\
			FALCON_HELPER_VALUE_TEST(Falcon_T);\
		};\
		\
		typedef typename std::add_const<Falcon_T>::type Falcon_T_const;\
		\
	public:\
		static const bool value = impl<Falcon_T, _Functor(Falcon_T::*)(_Args...)>::value || impl<Falcon_T_const, _Functor(Falcon_T_const::*)(_Args...)>::value;\
	}

# define FALCON_HAS_SIGNATURE_NAME(_FuncName) has_##_FuncName##_signature

# define FALCON_CLASS_HAS_SIGNATURE(_FuncName)\
	FALCON_CREATE_HAS_SIGNATURE(FALCON_HAS_SIGNATURE_NAME(_FuncName), _FuncName)
#endif

#endif
