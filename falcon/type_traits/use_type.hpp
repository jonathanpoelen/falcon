#ifndef FALCON_TYPE_TRAITS_USE_TYPE_HPP
#define FALCON_TYPE_TRAITS_USE_TYPE_HPP

namespace falcon
{
	template <typename _T>
	struct use_type
	{
		typedef _T type;
	};
}

#endif