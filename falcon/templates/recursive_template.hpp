#ifndef _FALCON_TEMPLATES_RECURSIVE_TEMPLATE_HPP
#define _FALCON_TEMPLATES_RECURSIVE_TEMPLATE_HPP

#include <cstddef> //std::size_t
#include <falcon/c++/pack.hpp>
#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/detail/typeof.hpp>

namespace falcon {
	template<template<class CPP_PACK> class _TemplateFunctor, template<class CPP_PACK> class _Template, std::size_t _MaxDepth = -1, bool _ErrFirstCallFunctorIsFalse = false>
	struct recursive_template
	{
		template<typename CPP_PACK _T>
		class type_wrapper
		{
			template<bool, std::size_t, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl_recursive
			{};

			template<std::size_t _Depth, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl_recursive<true, _Depth, parameter_pack<_U CPP_USE_OPTIONAL_PACK(_Args)> >
			{
				typedef typename _Template<_U CPP_USE_OPTIONAL_PACK(_Args)>::type __first_type;
				typedef __impl_recursive<_Depth-1 && _TemplateFunctor<_U CPP_USE_OPTIONAL_PACK(_Args)>::value, _Depth-1,  parameter_pack<__first_type CPP_USE_OPTIONAL_PACK(_Args)> > __type;
				typedef typename __type::type type;
				static const std::size_t depth = __type::depth;
			};
			template<std::size_t _Depth, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl_recursive<false, _Depth, parameter_pack<_U CPP_USE_OPTIONAL_PACK(_Args)> >
			{
				typedef _U type;
				static const std::size_t depth = _Depth;
			};

			template<bool, std::size_t, typename CPP_PACK _U>
			struct __impl
			{};
			template<std::size_t _Depth, typename CPP_PACK _U>
			struct __impl<true, _Depth, parameter_pack<_U CPP_PACK> >
			{
				typedef __impl_recursive<_Depth, _Depth, parameter_pack<_U CPP_PACK> > __type;
				typedef typename __type::type type;
				static const std::size_t depth = __type::depth;
			};

			static const bool __test = !_ErrFirstCallFunctorIsFalse || _TemplateFunctor<_T CPP_PACK>::value;

#if __cplusplus >= 201103L
			static_assert(__test, "first call functor is false");
#endif

			typedef __impl<__test, _MaxDepth, parameter_pack<_T CPP_PACK> > __type;

		public:
			typedef typename __type::type type;
			static const std::size_t depth = _MaxDepth - __type::depth;
		};

		template<typename CPP_PACK _T>
		class value_wrapper
		{
			template<bool, std::size_t, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl_recursive
			{};

			template<std::size_t _Depth, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl_recursive<true, _Depth, parameter_pack<_U CPP_USE_OPTIONAL_PACK(_Args)> >
			{
				typedef typename _Template<_U CPP_USE_OPTIONAL_PACK(_Args)>::type __type;
				static const __FALCON_TYPEOF_INIT_WRAP_EXPR(value, (__impl_recursive<_Depth-1 && _TemplateFunctor<_U CPP_USE_OPTIONAL_PACK(_Args)>::value, _Depth-1, parameter_pack<__type CPP_USE_OPTIONAL_PACK(_Args)> >::value));
			};
			template<std::size_t _Depth, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl_recursive<false, _Depth, parameter_pack<_U CPP_USE_OPTIONAL_PACK(_Args)> >
			{
				static const __FALCON_TYPEOF_INIT_WRAP_EXPR(value, (_Template<_U CPP_USE_OPTIONAL_PACK(_Args)>::value));
			};

			template<bool, std::size_t, typename CPP_PACK _U>
			struct __impl
			{};
			template<std::size_t _Depth, typename CPP_PACK _U>
			struct __impl<true, _Depth, parameter_pack<_U CPP_PACK> >
			{
				static const __FALCON_TYPEOF_INIT_WRAP_EXPR(value, (__impl_recursive<_Depth, _Depth, parameter_pack<_U CPP_PACK> >::value));
			};

			static const bool __test = !_ErrFirstCallFunctorIsFalse || _TemplateFunctor<_T CPP_PACK>::value;

#if __cplusplus >= 201103L
			static_assert(__test, "first call functor is false");
#endif

		public:
			static const __FALCON_TYPEOF_INIT_WRAP_EXPR(value, (__impl<__test, _MaxDepth, parameter_pack<_T CPP_PACK> >::value));
		};
	};
}

#endif
