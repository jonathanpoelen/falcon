#ifndef _FALCON_TUPLE_TUPLE_PACK_HPP
#define _FALCON_TUPLE_TUPLE_PACK_HPP

#include <falcon/tuple/parameter_pack.hpp>

namespace falcon {

template <typename _Tuple, typename _Indexes>
struct tuple_pack_element
: parameter_pack_to_tuple<
	typename tuple_to_parameter_pack_with_parameter_index<_Tuple, _Indexes>::type
>{};

}

#endif