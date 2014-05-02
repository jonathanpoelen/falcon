#ifndef _FALCON_TEMPLATES_TEMPLATE_BINARY_HPP
#define _FALCON_TEMPLATES_TEMPLATE_BINARY_HPP

#if __cplusplus >= 201103L
# include <type_traits>
#endif
#include <falcon/templates/detail/typeof.hpp>

namespace falcon {

#if __cplusplus >= 201103L
	template<class _Functor, template<class...> class _Temp, template<class...> class _Temp2>
	struct template_binary
	{
		template<typename... _Args>
		struct value_wrapper
		{
			static const decltype(_Functor()(_Temp<_Args...>::value, _Temp2<_Args...>::value)) value = _Functor()(_Temp<_Args...>::value, _Temp2<_Args...>::value);
		};

		template<typename... _Args>
		struct type_wrapper
		{
			typedef decltype(_Functor()(std::declval<typename _Temp<_Args...>::type>(), std::declval<typename _Temp2<_Args...>::type>())) type;
		};
	};
#endif

	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_plus;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_minus;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_multiplies;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_divides;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_negate;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_logical_and;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_logical_or;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_bit_and;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_bit_or;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_bit_xor;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_left_shift;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_right_shift;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_equal_to;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_not_equal_to;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_greater;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_less;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_greater_equal;
	template<template<class> class _Temp, template<class> class _Temp2>
	class template_binary_less_equal;

	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_plus;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_minus;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_multiplies;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_divides;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_negate;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_logical_and;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_logical_or;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_bit_and;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_bit_or;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_bit_xor;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_left_shift;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_right_shift;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_equal_to;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_not_equal_to;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_greater;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_less;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_greater_equal;
	template<template<class, class> class _Temp, template<class, class> class _Temp2>
	class template_binary2_less_equal;

#define __FALCON_CREATE_TEMPLATE_BINARY(name_op, op)\
	template<template<class> class _Temp, template<class> class _Temp2>\
	struct template_binary_##name_op\
	{\
		template<typename _T>\
		struct wrapper\
		{\
			typedef __FALCON_TYPEOF(_Temp<_T>::value op _Temp2<_T>::value) type;\
			static const type value = _Temp<_T>::value op _Temp2<_T>::value;\
		};\
	};\
	template<template<class, class> class _Temp, template<class, class> class _Temp2>\
	struct template_binary2_##name_op\
	{\
		template<typename _T, typename _U>\
		class wrapper\
		{\
			typedef _Temp<_T, _U> __type_temp;\
			typedef _Temp2<_T, _U> __type_temp2;\
		public:\
			typedef __FALCON_TYPEOF((__type_temp::value op __type_temp2::value)) type;\
			static const type value = _Temp<_T, _U>::value op _Temp2<_T, _U>::value;\
		};\
	};

	__FALCON_CREATE_TEMPLATE_BINARY(plus, +)
	__FALCON_CREATE_TEMPLATE_BINARY(minus, -)
	__FALCON_CREATE_TEMPLATE_BINARY(multiplies, *)
	__FALCON_CREATE_TEMPLATE_BINARY(divides, /)
	__FALCON_CREATE_TEMPLATE_BINARY(negate, -)
	__FALCON_CREATE_TEMPLATE_BINARY(logical_and, &&)
	__FALCON_CREATE_TEMPLATE_BINARY(logical_or, ||)
	__FALCON_CREATE_TEMPLATE_BINARY(bit_and, &)
	__FALCON_CREATE_TEMPLATE_BINARY(bit_or, |)
	__FALCON_CREATE_TEMPLATE_BINARY(bit_xor, ^)
	__FALCON_CREATE_TEMPLATE_BINARY(left_shift, <<)
	__FALCON_CREATE_TEMPLATE_BINARY(right_shift, >>)
	__FALCON_CREATE_TEMPLATE_BINARY(equal_to, ==)
	__FALCON_CREATE_TEMPLATE_BINARY(not_equal_to, !=)
	__FALCON_CREATE_TEMPLATE_BINARY(greater, >)
	__FALCON_CREATE_TEMPLATE_BINARY(less, <)
	__FALCON_CREATE_TEMPLATE_BINARY(greater_equal, >=)
	__FALCON_CREATE_TEMPLATE_BINARY(less_equal, <=)

#undef __FALCON_CREATE_TEMPLATE_BINARY
}

#endif
