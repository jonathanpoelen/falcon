#ifndef _FALCON_BIT_LEFT_BIT_HPP
#define _FALCON_BIT_LEFT_BIT_HPP

#include <falcon/bit/bit_size.hpp>

namespace falcon {
	template<typename _T>
	struct left_bit
	{
		static const _T value = _T(1) << (bit_size<_T>::value - 1);
	};
}

#endif