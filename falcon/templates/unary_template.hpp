#ifndef _FALCON_TEMPLATES_UNARY_TEMPLATE_HPP
#define _FALCON_TEMPLATES_UNARY_TEMPLATE_HPP

#if __cplusplus >= 201103L
# include <type_traits>
#endif
#include <falcon/detail/typeof.hpp>

namespace falcon {

#if __cplusplus >= 201103L
	template<class _Functor, template<class...> class _Temp>
	struct template_unary
	{
		template<typename... _Args>
		struct value_wrapper
		{
			static const decltype(_Functor()(_Temp<_Args...>::value)) value = _Functor()(_Temp<_Args...>::value);
		};

		template<typename... _Args>
		struct type_wrapper
		{
			typedef decltype(_Functor()(std::declval<typename _Temp<_Args...>::type>())) type;
		};
	};
#endif

	template<template<class> class _Template>
	class template_unary_plus;
	template<template<class> class _Template>
	class template_unary_negate;
	template<template<class> class _Template>
	class template_unary_complement;
	template<template<class> class _Template>
	class template_unary_pointer;
	template<template<class> class _Template>
	class template_unary_address;

	template<template<class, class> class _Template>
	class template_unary2_plus;
	template<template<class, class> class _Template>
	class template_unary2_negate;
	template<template<class, class> class _Template>
	class template_unary2_complement;
	template<template<class, class> class _Template>
	class template_unary2_pointer;
	template<template<class, class> class _Template>
	class template_unary2_address;

#define __FALCON_CREATE_TEMPLATE_UNARY(name_op, op)\
	template<template<class> class _Temp>\
	struct template_unary_##name_op\
	{\
		template<typename _T>\
		struct wrapper\
		{\
			typedef __FALCON_TYPEOF(op(_Temp<_T>::value)) type;\
			static const type value = op(_Temp<_T>::value);\
		};\
	};\
	template<template<class, class> class _Temp>\
	struct template_unary2_##name_op\
	{\
		template<typename _T, typename _U>\
		struct wrapper\
		{\
			typedef __FALCON_TYPEOF(op(_Temp<_T, _U>::value)) type;\
			static const type value = op(_Temp<_T, _U>::value);\
		};\
	};

	__FALCON_CREATE_TEMPLATE_UNARY(plus, +)
	__FALCON_CREATE_TEMPLATE_UNARY(negate, -)
	__FALCON_CREATE_TEMPLATE_UNARY(complement, ~)
	__FALCON_CREATE_TEMPLATE_UNARY(pointer, *)
	__FALCON_CREATE_TEMPLATE_UNARY(address, &)

#undef __FALCON_CREATE_TEMPLATE_UNARY
}

#endif