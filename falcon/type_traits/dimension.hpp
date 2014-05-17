#ifndef _FALCON_TYPE_TRAITS_DIMENSION_HPP
#define _FALCON_TYPE_TRAITS_DIMENSION_HPP

#include <falcon/container/contains_range_access.hpp>

namespace falcon {

template <typename _T>
class dimension
{
	template<bool, typename _U = _T>
	struct dimension_child
	{
		static const std::size_t value = 0;
	};

	template<typename _U>
	struct dimension_child<true, _U>
	{
		static const std::size_t value = 1 + dimension<typename range_access_subtype<_T>::type>::value;
	};

public:
	static const std::size_t value = dimension_child<contains_range_access_iterator<_T>::value>::value;
};

}

#endif
