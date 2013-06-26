#ifndef FALCON_SFINAE_HAS_TYPE_HPP
#define FALCON_SFINAE_HAS_TYPE_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/yes_no_type.hpp>

#define __FALCON_HELPER_VALUE_TEST(_T)\
	public:\
		static const bool value = sizeof(test(static_cast<_T*>(0))) == sizeof(::falcon::yes_type);\
		typedef bool value_type;\
		typedef ::falcon::integral_constant<bool, value> type;

#if __cplusplus >= 201103L
#define FALCON_HELPER_VALUE_TEST(_T)\
	__FALCON_HELPER_VALUE_TEST(_T)\
	constexpr operator bool() { return value; }
#else
#define FALCON_HELPER_VALUE_TEST(_T) __FALCON_HELPER_VALUE_TEST(_T)
#endif

#define FALCON_CREATE_HAS_TYPE(_Name, _TypeName)\
template<typename _Falcon_T>\
	class _Name {\
		template<typename _Falcon_T1>\
		struct __type_yes_test{ typedef _Falcon_T1* type; };\
		template<typename _Falcon_T1>\
		struct __type_yes_test<_Falcon_T1&>{ typedef _Falcon_T1* type; };\
		template<typename _U>\
		static ::falcon::yes_type test(_U*, typename __type_yes_test<typename _U::_TypeName>::type = 0);\
		static ::falcon::no_type test(...);\
		FALCON_HELPER_VALUE_TEST(_Falcon_T)\
	}

#define FALCON_HAS_TYPE_NAME(_TypeName) has_##_TypeName

#define FALCON_CLASS_HAS_TYPE(_TypeName)\
	FALCON_CREATE_HAS_TYPE(FALCON_HAS_TYPE_NAME(_TypeName), _TypeName)

#endif
