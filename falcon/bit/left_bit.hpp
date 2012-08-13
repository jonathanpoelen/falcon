#ifndef _FALCON_BIT_LEFT_BIT_HPP
#define _FALCON_BIT_LEFT_BIT_HPP

namespace falcon {
	template<typename _T>
	struct left_bit
	{
		static const _T value = _T(1) << (sizeof(_T) * 8 - 1);
	};
}

#endif