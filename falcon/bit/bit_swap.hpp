#ifndef _FALCON_BIT_BIT_SWAP_HPP
#define _FALCON_BIT_BIT_SWAP_HPP

#include <falcon/bit/bit_size.hpp>
#include <falcon/bit/detail/bit_swap.hpp>
#include <falcon/detail/addressof.hpp>
#include <falcon/cast/unreliable_pointer_cast.hpp>

namespace falcon {

	inline void bit_swap(char* n, std::size_t size)
	{
		char *end = n + size;
		for (char c; n < end; ++n)
		{
			c = static_cast<char>((*n & 1) << 7
			| (*n & 2) << 5
			| (*n & 4) << 3
			| (*n & 8) << 1
			| (*n & 16) >> 1
			| (*n & 32) >> 3
			| (*n & 64) >> 5
			| (*n & 128) >> 7);
			--end;
			*n = static_cast<char>((*end & 1) << 7
			| (*end & 2) << 5
			| (*end & 4) << 3
			| (*end & 8) << 1
			| (*end & 16) >> 1
			| (*end & 32) >> 3
			| (*end & 64) >> 5
			| (*end & 128) >> 7);
			*end = c;
		}
		if (n != end)
			falcon::detail::bit::bit8_swap(*unreliable_pointer_cast<uint8_t>(n-1));
	}

	template<typename _T, unsigned int _S = bit_size<_T>::value>
	struct __bit_swap
	{
		inline static void __impl(_T& bits)
		{ bit_swap(falcon::unreliable_pointer_cast<char>(falcon::detail::addressof<>(bits)), sizeof(_T)); }
	};

#define __FALCON_CREATE_BIT_SWAP(S)\
	template<>\
	struct __bit_swap<uint##S##_t, S>\
	{\
		inline static void __impl(uint##S##_t& bits)\
		{ falcon::detail::bit::bit##S##_swap(bits); }\
	};\
	template<typename _T>\
	struct __bit_swap<_T, S>\
	{\
		inline static void __impl(_T& bits)\
		{ falcon::detail::bit::bit##S##_swap(*unreliable_pointer_cast<uint##S##_t>(&bits)); }\
	};

	__FALCON_CREATE_BIT_SWAP(8)
	__FALCON_CREATE_BIT_SWAP(16)
	__FALCON_CREATE_BIT_SWAP(32)
	__FALCON_CREATE_BIT_SWAP(64)

#undef __FALCON_CREATE_BIT_SWAP

	template <typename _T>
	void bit_swap(_T& bits)
	{ __bit_swap<_T>::__impl(bits); }

}

#endif