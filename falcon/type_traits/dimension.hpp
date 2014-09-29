#ifndef FALCONTYPETRAITS_DIMENSION_HPP
#define FALCONTYPETRAITS_DIMENSION_HPP

#include <falcon/container/contains_range_access.hpp>
#include <falcon/container/range_access.hpp>

namespace falcon {

template <typename T>
class dimension
{
	template<bool, typename U = T>
	struct dimension_child
	{ static const std::size_t value = 0; };

	template<typename U>
	struct dimension_child<true, U>
	{
		static const std::size_t value = 1
      + dimension<typename range_access_subtype<T>::type>::value;
	};

public:
	static const std::size_t value
    = dimension_child<contains_range_access_iterator<T>::value>::value;
};

}

#endif
