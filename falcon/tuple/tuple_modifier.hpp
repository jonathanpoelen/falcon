#ifndef _FALCON_TUPLE_TUPLE_MODIFIER_HPP
#define _FALCON_TUPLE_TUPLE_MODIFIER_HPP

#include <falcon/tuple/parameter_pack.hpp>
#include <falcon/parameter/manip.hpp>

namespace falcon {

template <template<class...> class _Modifier, typename _Tuple,
	typename _Indexes = typename build_parameter_index<
		std::tuple_size<_Tuple>::value
	>::type
>
struct tuple_modifier
{
	typedef typename parameter_pack_to_tuple<
		typename parameter::modifier<
			_Modifier,
			typename tuple_to_parameter_pack_with_parameter_index<
				_Tuple, _Indexes
			>::type
		>::type
	>::type type;
};

}

#endif
