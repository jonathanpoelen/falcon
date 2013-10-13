#ifndef _FALCON_BIT_BIT_SWAP_HPP
#define _FALCON_BIT_BIT_SWAP_HPP

#include <falcon/bit/size.hpp>
#include <falcon/bit/detail/bit_swap.hpp>
#include <falcon/detail/addressof.hpp>
#include <falcon/cast/unreliable_pointer_cast.hpp>

namespace falcon {
	inline char __get_char_swap(char c)
	{
#if __CHAR_BIT__ == 8
		return static_cast<char>((c & 1) << 7
		| (c & 2) << 5
		| (c & 4) << 3
		| (c & 8) << 1
		| (c & 16) >> 1
		| (c & 32) >> 3
		| (c & 64) >> 5
		| (c & 128) >> 7);
#elif __CHAR_BIT__ == 7
		return static_cast<char>((c & 1) << 6
		| (c & 2) << 4
		| (c & 4) << 2
		| (c & 8)
		| (c & 16) >> 2
		| (c & 32) >> 3
		| (c & 64) >> 6);
#else
#error unimplemented swap on char
#endif
	}

	inline void bit_swap(char* n, std::size_t size)
	{
		char *end = n + size;
		for (char c; n < end; ++n)
		{
			c = __get_char_swap(*n);
			--end;
			*n = __get_char_swap(*end);
			*end = c;
		}
		if (n != end)
		{
			--n;
			*n = __get_char_swap(*n);
		}
	}

	template<typename _T, unsigned int _S = bit::size<_T>::value>
	struct __bit_swap
	{
		inline static void __impl(_T& bits)
		{ bit_swap(falcon::unreliable_pointer_cast<char>(falcon::detail::addressof(bits)), sizeof(_T)); }
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
