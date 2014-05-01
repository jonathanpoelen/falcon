#ifndef _FALCON_TEMPLATES_LOOP_TEMPLATE_HPP
#define _FALCON_TEMPLATES_LOOP_TEMPLATE_HPP

#include <cstddef> //std::size_t
#include <falcon/c++/pack.hpp>
#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/detail/typeof.hpp>

namespace falcon {
	template <std::size_t _NmLoop, template<class CPP_PACK> class _Template>
	struct loop_template
	{
		template <typename CPP_PACK _T>
		class type_wrapper
		{
			template <std::size_t _N, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl
			{};

			template <std::size_t _N, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl<_N, parameter_pack<_U CPP_USE_OPTIONAL_PACK(_Args)> >
			{
				typedef typename __impl<_N-1, parameter_pack<typename _Template<_U CPP_USE_OPTIONAL_PACK(_Args)>::type CPP_USE_OPTIONAL_PACK(_Args)> >::type type;
			};

			template <typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl<0, parameter_pack<_U CPP_USE_OPTIONAL_PACK(_Args)> >
			{
				typedef typename _Template<_U CPP_USE_OPTIONAL_PACK(_Args)>::type type;
			};

		public:
			typedef typename __impl<_NmLoop, parameter_pack<_T CPP_PACK> >::type type;
		};

		template <typename CPP_PACK _T>
		struct value_wrapper
		{
			template <std::size_t _N, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl
			{};

			template <std::size_t _N, typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl<_N, parameter_pack<_U CPP_USE_OPTIONAL_PACK(_Args)> >
			{
				static const __FALCON_TYPEOF_INIT_WRAP_EXPR(value, (__impl<_N-1, parameter_pack<typename _Template<_U CPP_USE_OPTIONAL_PACK(_Args)>::type CPP_USE_OPTIONAL_PACK(_Args)> >::value));
			};

			template <typename _U CPP_OPTIONAL_PACK(_Args)>
			struct __impl<0, parameter_pack<_U CPP_USE_OPTIONAL_PACK(_Args)> >
			{
				static const __FALCON_TYPEOF_INIT_WRAP_EXPR(value, (_Template<_U CPP_USE_OPTIONAL_PACK(_Args)>::value));
			};

		public:
			static const __FALCON_TYPEOF_INIT_WRAP_EXPR(value, (__impl<_NmLoop, parameter_pack<_T CPP_PACK> >::value));
		};
	};
}

#endif
