#ifndef _FALCON_TUPLE_TUPLE_MODIFIER_HPP
#define _FALCON_TUPLE_TUPLE_MODIFIER_HPP

#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/parameter/manip.hpp>

namespace falcon {

template <template<class...> class _Modifier, typename _Tuple>
struct tuple_modifier
{
	typedef typename parameter_pack_to_tuple<
		typename parameter::pack_modifier<
			_Modifier,
			typename tuple_to_parameter_pack<_Tuple>::type
		>::type
	>::type type;
};

}

#endif