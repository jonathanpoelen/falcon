#ifndef _FALCON_TEMPLATES_TEMPLATE_TYPE_HPP
#define _FALCON_TEMPLATES_TEMPLATE_TYPE_HPP

namespace falcon {

	template <typename _T>
	struct template_type
	{
#if __cplusplus > 201100L
		template<typename...>
		struct filter
		{
			typedef _T type;
		};
#else
		template<typename __T = void, typename _U = void, typename _V = void>
		struct filter
		{
			typedef _T type;
		};
#endif
	};

}

#endif