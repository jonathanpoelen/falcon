#ifndef _FALCON_ARG_REVERSE_ARG_HPP
#define _FALCON_ARG_REVERSE_ARG_HPP

#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/arg/arg.hpp>

namespace falcon {

template<std::size_t _N, typename _Packs, typename... _Args>
class __reverse_arg;

template<std::size_t _N, typename... _Elements, typename... _Args>
struct __reverse_arg<_N, parameter_pack<_Elements...>, _Args...>
{
	typedef typename __reverse_arg<_N-1, parameter_pack<_Elements..., typename arg_element<_N-1, _Args...>::type>, _Args...>::type type;
};

template<typename... _Elements, typename... _Args>
struct __reverse_arg<0, parameter_pack<_Elements...>, _Args...>
{
	typedef parameter_pack<_Elements...> type;
};

template<typename... _Args>
struct reverse_arg
{
	typedef typename __reverse_arg<sizeof...(_Args), parameter_pack<>, _Args...>::type type;
};
}

#endif
