#ifndef _FALCON_TEMPLATES_TEMPLATE_TO_TYPE_HPP
#define _FALCON_TEMPLATES_TEMPLATE_TO_TYPE_HPP

namespace falcon {
#if __cplusplus >= 201103L
	template <template<class...> class _Temp>
	struct template_to_type
	{
		template<typename... _Args>
		struct filter
		{
			typedef typename _Temp<_Args...>::type type;
		};
	};
#else
	template <template<class> class _Temp>
	struct template_to_type
	{
		template<typename _T>
		struct filter
		{
			typedef typename _Temp<_T>::type type;
		};
	};
#endif
}

#endif