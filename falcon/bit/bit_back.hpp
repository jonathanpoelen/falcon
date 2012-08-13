#ifndef _FALCON_BIT_BIT_BACK_HPP
#define _FALCON_BIT_BIT_BACK_HPP

#include <falcon/bit/bit_size.hpp>

namespace falcon {
	///bit-size<_T>::value - 1
	template <typename _T, typename _Result = unsigned>
	struct bit_back
	{
		static const _Result value = bit_size<_T>::value - 1;
	};
}

#endif