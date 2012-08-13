#ifndef _FALCON_BIT_BIT_SIZE_HPP
#define _FALCON_BIT_BIT_SIZE_HPP

#include <cstddef>

namespace falcon {
	template <typename _T>
	struct bit_size
	{
		static const std::size_t value = 8 * sizeof(_T);
	};
}

#endif