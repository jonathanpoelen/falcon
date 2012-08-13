#ifndef _FALCON_BIT_LAST_BIT_HPP
#define _FALCON_BIT_LAST_BIT_HPP

#include <falcon/bit/edge_bit.hpp>

namespace falcon {

	template <typename _T>
	_T last_bit(const _T& d)
	{
		if (!d)
			return right_bit<_T>::value;
		_T dd = left_bit<_T>::value;
		if (dd == d)
			return d;
		do {
			dd >>= 1;
		} while (dd > d);
		return dd << 1;
	}

}

#endif