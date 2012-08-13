#ifndef _FALCON_BIT_FILL_BIT_HPP
#define _FALCON_BIT_FILL_BIT_HPP

#include <falcon/bit/bit_size.hpp>

namespace falcon {
	template <typename _T, std::size_t _NRight = bit_size<_T>::value>
	struct fill_bit
	{
		static const _T value = _T(~0LL) >> (bit_size<_T>::value - _NRight);
	};
}

#endif