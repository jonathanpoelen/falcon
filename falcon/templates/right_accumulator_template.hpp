#ifndef _FALCON_TEMPLATES_RIGHT_ACCUMULATOR_TEMPLATE_HPP
#define _FALCON_TEMPLATES_RIGHT_ACCUMULATOR_TEMPLATE_HPP

#ifndef __GXX_EXPERIMENTAL_CXX0X__
# include <boost/typeof/typeof.hpp>
#endif

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<template<class...> class _Temp, typename... _RightArgs>
	struct template_right_accumulator
	{
		template<typename... _Args>
		struct value_wrapper
		{
			static const decltype(_Temp<_Args..., _RightArgs...>::value) value = _Temp<_Args..., _RightArgs...>::value;
		};

		template<typename... _Args>
		struct type_wrapper
		{
			typedef typename _Temp<_Args..., _RightArgs...>::type type;
		};
	};
#else
	template<template<class, class> class _Template, typename _RightArg>
	struct template_right_accumulator
	{
		template<typename _T>
		class value_wrapper
		{
			static const BOOST_TYPEOF((_Template<_T, _RightArg>::value)) value = _Template<_T, _RightArg>::value;
		};

		template<typename _T>
		struct type_wrapper
		{
			typedef typename _Template<_T, _RightArg>::type type;
		};
	};
#endif

}

#endif