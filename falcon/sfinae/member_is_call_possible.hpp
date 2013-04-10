#ifndef _FALCON_SFINAE_MEMBER_IS_CALL_POSSIBLE_HPP
#define _FALCON_SFINAE_MEMBER_IS_CALL_POSSIBLE_HPP

#include <falcon/sfinae/has_member.hpp>
#include <falcon/type_traits/invalid_type.hpp>
#include <falcon/type_traits/cv_selector.hpp>

#if __cplusplus > 201100L
# define FALCON_CREATE_MEMBER_FUNCTION_IS_CALL_POSSIBLE(_Name, _FuncName, _HasMember)\
	template <typename _Falcon_T, typename... _Falcon_Args>\
	class _Name\
	{\
		template<bool, bool, typename T>\
		struct impl {\
			typedef ::falcon::invalid_type result_type;\
		};\
		template<typename T, bool b>\
		struct impl<true, b, T> {\
			struct __derived : public _Falcon_T{\
				using _Falcon_T::_FuncName;\
				::falcon::invalid_type _FuncName(...) const;\
			};\
			\
			typedef decltype(std::declval<typename ::falcon::match_cv_qualifiers<_Falcon_T, __derived>::type>()._FuncName(std::declval<_Falcon_Args>()...)) result_type;\
		};\
		\
		template<typename T>\
		struct impl<true, true, T> {\
			template <typename U, typename _Result = decltype(std::declval<U>()._FuncName())>\
			static _Result test(U*);\
			static ::falcon::invalid_type test(...);\
			\
			typedef decltype(test(static_cast<_Falcon_T *>(0))) result_type;\
		};\
		\
		typedef impl<_HasMember<_Falcon_T>::value, !sizeof...(_Falcon_Args), _Falcon_T> impl_type;\
		\
	public:\
		typedef typename impl_type::result_type result_type;\
		static const bool value = !::falcon::is_invalid<result_type>::value;\
	}
#else
# define FALCON_CREATE_MEMBER_FUNCTION_IS_CALL_POSSIBLE(_Name, _FuncName, _HasMember)\
	template <typename _Falcon_T, typename... _Falcon_Args>\
	class _Name\
	{ static const bool value = false; }
#endif

#define FALCON_MEMBER_FUNCTION_IS_CALL_POSSIBLE_NAME(_FuncName) _FuncName##_member_is_call_possible

#define FALCON_CLASS_MEMBER_FUNCTION_IS_CALL_POSSIBLE(_FuncName)\
	FALCON_CREATE_MEMBER_FUNCTION_IS_CALL_POSSIBLE(FALCON_MEMBER_FUNCTION_IS_CALL_POSSIBLE_NAME(_FuncName), _FuncName, FALCON_HAS_MEMBER_FUNCTION_NAME(_FuncName))

#if __cplusplus > 201100L
# define FALCON_CREATE_MEMBER_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT(_Name, _IsCallPossible)\
	template <typename _Falcon_T, typename _Signature>\
	class _Name\
	{};\
	\
	template <typename _Falcon_T, typename _ResultOf, typename... _Falcon_Args>\
	class _Name<_Falcon_T, _ResultOf(_Falcon_Args...)>\
	{\
		typedef _IsCallPossible<_Falcon_T, _Falcon_Args...> member_is_call_possible_type;\
		\
		template<bool, typename T>\
		struct impl {\
			static const bool value = false;\
		};\
		template<typename T>\
		struct impl<true, T> {\
			static const bool value = std::is_convertible<_ResultOf, typename member_is_call_possible_type::result_type>::value;\
		};\
	\
	public:\
		static const bool value = impl<member_is_call_possible_type::value, _Falcon_T>::value;\
	}
#else
# define FALCON_CREATE_MEMBER_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT(_Name, _IsCallPossible)\
	template <typename _Falcon_T, typename _ResultOf, typename... _Falcon_Args>\
	struct _Name\
	{ static const bool value = false; }
#endif

#define FALCON_MEMBER_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT_NAME(_FuncName) _FuncName##_member_is_call_possible_and_convertible_result

#define FALCON_CLASS_MEMBER_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT(_FuncName) FALCON_CREATE_MEMBER_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT(FALCON_MEMBER_FUNCTION_IS_CALL_POSSIBLE_AND_CONVERTIBLE_RESULT_NAME(_FuncName), FALCON_MEMBER_FUNCTION_IS_CALL_POSSIBLE_NAME(_FuncName))

#endif
