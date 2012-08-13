#ifndef _FALCON_ALGORITHM_FOR_N_HPP
#define _FALCON_ALGORITHM_FOR_N_HPP

#include <falcon/preprocessor/move.hpp>

namespace falcon {

template<typename _ForwardIerator, typename _Functor>
_Functor for_n(_ForwardIerator it, std::size_t n, _Functor func)
{
	for (; n; ++it, --n)
		func(*it);
	return FALCON_MOVE(func);
}

}

#endif
