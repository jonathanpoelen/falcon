#ifndef _FALCON_TUPLE_PARAMETER_PACK_HPP
#define _FALCON_TUPLE_PARAMETER_PACK_HPP

#include <tuple>
#include <falcon/parameter/parameter_pack.hpp>

namespace falcon {

template<typename>
struct tuple_to_parameter_pack;

template<typename... _Elements>
struct tuple_to_parameter_pack<std::tuple<_Elements...>>
{
	typedef parameter_pack<_Elements...> type;
};

template<typename>
struct parameter_pack_to_tuple;

template<typename... _Elements>
struct parameter_pack_to_tuple<parameter_pack<_Elements...>>
{
	typedef std::tuple<_Elements...> type;
};

}

#endif