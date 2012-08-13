#ifndef _FALCON_TEMPLATES_TEMPLATE_SIZE_HPP
#define _FALCON_TEMPLATES_TEMPLATE_SIZE_HPP

#include <cstddef>

namespace falcon {

#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<typename... _Args>
	struct template_size
	{
		static const std::size_t value = sizeof...(_Args);
	};
#else
	struct __template_size_default;

	template<
		typename _T1 = __template_size_default,
		typename _T2 = __template_size_default,
		typename _T3 = __template_size_default,
		typename _T4 = __template_size_default,
		typename _T5 = __template_size_default,
		typename _T6 = __template_size_default,
		typename _T7 = __template_size_default,
		typename _T8 = __template_size_default,
		typename _T9 = __template_size_default,
		typename _T10 = __template_size_default,
		typename _T11 = __template_size_default,
		typename _T12 = __template_size_default,
		typename _T13 = __template_size_default,
		typename _T14 = __template_size_default,
		typename _T15 = __template_size_default,
		typename _T16 = __template_size_default,
		typename _T17 = __template_size_default,
		typename _T18 = __template_size_default,
		typename _T19 = __template_size_default,
		typename _T20 = __template_size_default,
		typename _T21 = __template_size_default,
		typename _T22 = __template_size_default,
		typename _T23 = __template_size_default,
		typename _T24 = __template_size_default,
		typename _T25 = __template_size_default,
		typename _T26 = __template_size_default,
		typename _T27 = __template_size_default,
		typename _T28 = __template_size_default,
		typename _T29 = __template_size_default
	>
	class template_size
	{
		template<typename _T>
		struct is_default
		{ static const bool value = false; };

		template<>
		struct is_default<__template_size_default>
		{ static const bool value = true; };

		static const std::size_t value = (is_default<_T1>::value ? 1 : (is_default<_T2>::value ? 2 : (is_default<_T3>::value ? 3 : (is_default<_T4>::value ? 4 : (is_default<_T5>::value ? 5 : (is_default<_T6>::value ? 6 : (is_default<_T7>::value ? 7 : (is_default<_T8>::value ? 8 : (is_default<_T9>::value ? 9 : (is_default<_T10>::value ? 10 : (is_default<_T11>::value ? 11 : (is_default<_T12>::value ? 12 : (is_default<_T13>::value ? 13 : (is_default<_T14>::value ? 14 : (is_default<_T15>::value ? 15 : (is_default<_T16>::value ? 16 : (is_default<_T17>::value ? 17 : (is_default<_T18>::value ? 18 : (is_default<_T19>::value ? 19 : (is_default<_T20>::value ? 20 : (is_default<_T21>::value ? 21 : (is_default<_T22>::value ? 22 : (is_default<_T23>::value ? 23 : (is_default<_T24>::value ? 24 : (is_default<_T25>::value ? 25 : (is_default<_T26>::value ? 26 : (is_default<_T27>::value ? 27 : (is_default<_T28>::value ? 28 : (is_default<_T29>::value ? 29 : 30))))))))))))))))))))))))))))) - 1;
	};
#endif

}

#endif