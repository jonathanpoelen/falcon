#ifndef _FALCON_TEMPLATES_OR_TEMPLATE_HPP
#define _FALCON_TEMPLATES_OR_TEMPLATE_HPP

#if __cplusplus >= 201103L
# include <falcon/templates/template_pack.hpp>
#endif

namespace falcon {

#if __cplusplus >= 201103L
	template<template<class...> class... _Temps>
	struct template_or
	{
		template<typename... _Args>
		class filter
		{
			template<typename _Pack>
			struct __impl;

			template<template<class...> class __Temp, template<class...> class... __Temps>
			struct __impl<template_pack<__Temp, __Temps...>>
			{
				static const bool value = __Temp<_Args...>::value || __impl<template_pack<__Temps...>>::value;
			};

			template<template<class...> class __Temp>
			struct __impl<template_pack<__Temp>>
			{
				static const decltype(__Temp<_Args...>::value) value = __Temp<_Args...>::value;
			};

			typedef __impl<template_pack<_Temps...>> impl;

		public:
			static const decltype(impl::value) value = impl::value;
		};
	};
#else
	template<typename>
	struct __template_or
	{ static const bool value = false; };

	template<template<class> class _Template, template<class> class _Template2 = __template_or>
	struct template_or
	{
		template<typename _T>
		struct filter
		{
			static const bool value = _Template<_T>::value || _Template2<_T>::value;
		};
	};
#endif

}

#endif