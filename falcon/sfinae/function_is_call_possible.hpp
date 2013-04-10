#ifndef _FALCON_SFINAE_FUNCTION_IS_CALL_POSSIBLE_HPP
#define _FALCON_SFINAE_FUNCTION_IS_CALL_POSSIBLE_HPP

#include <type_traits>
#include <falcon/type_traits/yes_no_type.hpp>

#if __cplusplus > 201100L
# define FALCON_CREATE_FUNCTION_IS_CALL_POSSIBLE(_Name, _FuncName)\
	template <typename... _Falcon_Args>\
	class _Name\
	{\
		template<typename... __Falcon_Args>\
		static auto test(__Falcon_Args... args) -> decltype(_FuncName(std::declval<__Falcon_Args&>()...));\
		template<typename... __Falcon_Args>\
		static ::falcon::no_type test(...);\
	public:\
		typedef decltype(test<_Falcon_Args...>(std::declval<_Falcon_Args>()...)) result_type;\
		static const bool value = !::falcon::is_no_type<result_type>::value;\
	}
#else
# define FALCON_CREATE_FUNCTION_IS_CALL_POSSIBLE(_Name, _FuncName)\
	template <typename... _Falcon_Args>\
	class _Name\
	{ static const bool value = false; }
#endif


#define FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(_FuncName) _FuncName##_function_is_call_possible

#define FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE(_FuncName)\
	FALCON_CREATE_FUNCTION_IS_CALL_POSSIBLE(FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(_FuncName), _FuncName)

#define FALCON_CLASS_FUNCTION_NAMESPACE_IS_CALL_POSSIBLE(_Namespace, _FuncName)\
FALCON_CREATE_FUNCTION_IS_CALL_POSSIBLE(FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(_FuncName), _Namespace::_FuncName)


#if __cplusplus > 201100L
# define FALCON_CREATE_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT(_Name, _IsCallPossible)\
	template <typename _Falcon_Signature>\
	class _Name\
	{};\
	\
	template <typename _Falcon_Result, typename... _Falcon_Args>\
	class _Name<_Falcon_Result(_Falcon_Args...)>\
	{\
		typedef _IsCallPossible<_Falcon_Args...> function_is_call_possible_type;\
		\
		template<bool, typename T>\
		struct impl {\
			static const bool value = false;\
		};\
		template<typename T>\
		struct impl<true, T> {\
			static const bool value = std::is_convertible<_Falcon_Result, typename function_is_call_possible_type::result_type>::value;\
		};\
	\
	public:\
		static const bool value = impl<function_is_call_possible_type::value>::value;\
	};
#else
# define FALCON_CREATE_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT(_Name, _IsCallPossible)\
	template <typename _Falcon_T, typename _Falcon_Result, typename... _Falcon_Args>\
	struct _Name\
	{ static const bool value = false; };
#endif


#define FALCON_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT_NAME(_FuncName) _FuncName##_function_is_call_possible_and_convertible_result

#define FALCON_CLASS_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT(_FuncName) FALCON_CREATE_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT(FALCON_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT_NAME(_FuncName), FALCON_FUNCTION_IS_CALL_POSSIBLE_NAME(_FuncName))

#endif
