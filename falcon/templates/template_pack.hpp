#ifndef _FALCON_TEMPLATES_TEMPLATE_PACK_HPP
#define _FALCON_TEMPLATES_TEMPLATE_PACK_HPP

namespace falcon {
#if __cplusplus > 201100L
	template<template<class...> class... _Temps>
	class template_pack;
#else
	template<typename>
	class template_pack;

	template<template<class> class _Temp>
	class __template_pack1;

	template<template<class> class _Temp>
	class template_pack<__template_pack1<_Temp> >
	{};

	template<template<class, class> class _Temp>
	class __template_pack2;

	template<template<class, class> class _Temp>
	class template_pack<__template_pack2<_Temp> >
	{};

	template<template<class, class, class> class _Temp>
	class __template_pack3;

	template<template<class, class, class> class _Temp>
	class template_pack<__template_pack3<_Temp> >
	{};
#endif
}

#endif