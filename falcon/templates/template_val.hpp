#ifndef _FALCON_TEMPLATES_TEMPLATE_VAL_HPP
#define _FALCON_TEMPLATES_TEMPLATE_VAL_HPP

namespace falcon {

	template <typename _T, _T _value>
	struct template_val
	{
#if __cplusplus > 201100L
		template<typename...>
		struct filter
		{
			static const _T value = _value;
		};
#else
		template<typename __T = void, typename _U = void, typename _V = void>
		struct filter
		{
			static const _T value = _value;
		};
#endif
	};

}

#endif