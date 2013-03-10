#ifndef FALCON_TUPLE_PARAMETER_INDEX_HPP
#define FALCON_TUPLE_PARAMETER_INDEX_HPP

#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/parameter/parameter_index.hpp>

namespace falcon {

template <typename _T>
struct build_tuple_index
{
	typedef typename build_parameter_index<
		std::tuple_size<_T>::value
	>::type type;
};

}

#endif