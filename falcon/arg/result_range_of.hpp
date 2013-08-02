#ifndef _FALCON_ARG_RESULT_RANGE_OF_HPP
#define _FALCON_ARG_RESULT_RANGE_OF_HPP

#include <falcon/parameter/result_pack_of.hpp>
#include <falcon/arg/arg_range.hpp>

namespace falcon {

template<std::size_t _Begin, std::size_t _Len, typename _Signature>
class result_range_of;

template<std::size_t _Begin, std::size_t _Len, typename _Function, typename... _Args>
struct result_range_of<_Begin, _Len, _Function(_Args...)>
{
	typedef typename parameter::result_of<_Function, typename arg_range<_Begin, _Len, _Args...>::type>::type type;
};

}

#endif
