#ifndef _FALCON_ARG_ARG_RANGE_HPP
#define _FALCON_ARG_ARG_RANGE_HPP

#include <falcon/parameter/keep_parameter_index.hpp>
#include <falcon/parameter/pack_element.hpp>
#include <falcon/parameter/parameter_pack.hpp>

namespace falcon {

template<std::size_t _Start, std::size_t _Len, typename... _Args>
struct arg_range
{
	typedef typename parameter::pack_element<
		parameter_pack<_Args...>,
		typename keep_parameter_index<
			range_parameter_index_tag<_Start, _Len>,
			sizeof...(_Args)
		>::type
	>::type type;
};

}

#endif
