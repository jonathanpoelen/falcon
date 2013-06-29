#ifndef FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP
#define FALCON_SFINAE_HAS_MEMBER_FUNCTION_HPP

#include <falcon/sfinae/sfinae.hpp>
#include <falcon/sfinae/has_type.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(is_class)

#define FALCON_CREATE_HAS_MEMBER_FUNCTION(_Name, _FuncName)\
	template <typename _Falcon_T,  bool = ::FALCON_BOOST_OR_STD_NAMESPACE::is_class<_Falcon_T>::value>\
	class _Name\
	{\
		struct base { void _FuncName(); };\
		struct derived : public _Falcon_T, public base {};\
		\
		template <typename U>\
		static ::falcon::no_type test(U*, ::falcon::sfinae::helper<void(base::*)(), &U::_FuncName>* = 0);\
		static ::falcon::yes_type test(...);\
		\
		FALCON_HELPER_VALUE_TEST(derived);\
	};\
	template <typename _Falcon_T>\
	struct _Name<_Falcon_T, false>\
	{ static const bool value = false; }

#define FALCON_HAS_MEMBER_FUNCTION_NAME(_FuncName) has_member_function_##_FuncName

#define FALCON_CLASS_HAS_MEMBER_FUNCTION(_FuncName)\
	FALCON_CREATE_HAS_MEMBER_FUNCTION(FALCON_HAS_MEMBER_FUNCTION_NAME(_FuncName), _FuncName)


#define FALCON_CREATE_HAS_MEMBER_VAR(_Name, _VarName)\
	template <typename _Falcon_T,  bool = ::FALCON_BOOST_OR_STD_NAMESPACE::is_class<_Falcon_T>::value>\
	class _Name\
	{\
		template <typename U, typename V = decltype(U::_VarName)>\
		static ::falcon::yes_type test(U*);\
		static ::falcon::no_type test(...);\
		\
		FALCON_HELPER_VALUE_TEST(_Falcon_T);\
	};\
	template <typename _Falcon_T>\
	struct _Name<_Falcon_T, false>\
	{ static const bool value = false; }

#define FALCON_HAS_MEMBER_VAR_NAME(_VarName) has_member_var_##_VarName

#define FALCON_CLASS_HAS_MEMBER_VAR(_VarName)\
	FALCON_CREATE_HAS_MEMBER_VAR(FALCON_HAS_MEMBER_VAR_NAME(_VarName), _VarName)

#if __cplusplus >= 201103L
# define FALCON_CREATE_HAS_SIGNATURE(_Name, _FuncName)\
	template <typename _Falcon_T, typename _Signature>\
	class _Name;\
	\
	template <typename _Falcon_T, typename _Functor, typename... _Args>\
	class _Name<_Falcon_T, _Functor(_Args...)>\
	{\
		template <typename T, typename _Member>\
		struct impl\
		{\
			template <typename U> static ::falcon::yes_type test(U*, ::falcon::sfinae::helper<_Member, &U::_FuncName>* = 0);\
			static ::falcon::no_type test(...);\
			FALCON_HELPER_VALUE_TEST(_Falcon_T);\
		};\
		\
		typedef typename std::add_const<_Falcon_T>::type _Falcon_T_const;\
		\
	public:\
		static const bool value = impl<_Falcon_T, _Functor(_Falcon_T::*)(_Args...)>::value || impl<_Falcon_T_const, _Functor(_Falcon_T_const::*)(_Args...)>::value;\
	}

# define FALCON_HAS_SIGNATURE_NAME(_FuncName) has_##_FuncName##_signature

# define FALCON_CLASS_HAS_SIGNATURE(_FuncName)\
	FALCON_CREATE_HAS_SIGNATURE(FALCON_HAS_SIGNATURE_NAME(_FuncName), _FuncName)
#endif

#endif
