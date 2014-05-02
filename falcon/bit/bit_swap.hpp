#ifndef FALCON_BIT_BIT_SWAP_HPP
#define FALCON_BIT_BIT_SWAP_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/bit/size.hpp>
#include <falcon/memory/addressof.hpp>
// #include <falcon/bit/bit_back.hpp>
// #include <falcon/type_traits/numeric/minimal_int.hpp>

namespace falcon {

/*template<typename T>
inline void generic_bit_swap(T& n) CPP_NOEXCEPT
{
  typedef typename minimal_int<bit_back<T>::value, char>::type int_type;
  int_type d = bit_back<T>::value;
  T b = 1;
  T ret = 0;
  for (; d != 1; b <<= 1, d -= 2)
    ret |= (n & b) << d;
  ret |= (n & b) << d;
  for (; d != bit_back<T>::value; d += 2)
    ret |= (n & (b <<= 1)) >> d;
  n = ret | (n & (b << 1)) >> d;
}*/

inline void bit8_swap(uint8_t& n) CPP_NOEXCEPT
{
  n = static_cast<uint8_t>((n & 1) << 7
  | (n & 2) << 5
  | (n & 4) << 3
  | (n & 8) << 1
  | (n & 16) >> 1
  | (n & 32) >> 3
  | (n & 64) >> 5
  | (n & 128) >> 7);
}

inline void bit16_swap(uint16_t& n) CPP_NOEXCEPT
{
  n = static_cast<uint16_t>((n & 1) << 15
  | (n & 2) << 13
  | (n & 4) << 11
  | (n & 8) << 9
  | (n & 16) << 7
  | (n & 32) << 5
  | (n & 64) << 3
  | (n & 128) << 1
  | (n & 256) >> 1
  | (n & 512) >> 3
  | (n & 1024) >> 5
  | (n & 2048) >> 7
  | (n & 4096) >> 9
  | (n & 8192) >> 11
  | (n & 16384) >> 13
  | (n & 32768) >> 15);
}

inline void bit32_swap(uint32_t& n) CPP_NOEXCEPT
{
  n = static_cast<uint32_t>((n & 1) << 31
  | (n & 2) << 29
  | (n & 4) << 27
  | (n & 8) << 25
  | (n & 16) << 23
  | (n & 32) << 21
  | (n & 64) << 19
  | (n & 128) << 17
  | (n & 256) << 15
  | (n & 512) << 13
  | (n & 1024) << 11
  | (n & 2048) << 9
  | (n & 4096) << 7
  | (n & 8192) << 5
  | (n & 16384) << 3
  | (n & 32768) << 1
  | (n & 65536) >> 1
  | (n & 131072) >> 3
  | (n & 262144) >> 5
  | (n & 524288) >> 7
  | (n & 1048576) >> 9
  | (n & 2097152) >> 11
  | (n & 4194304) >> 13
  | (n & 8388608) >> 15
  | (n & 16777216) >> 17
  | (n & 33554432) >> 19
  | (n & 67108864) >> 21
  | (n & 134217728) >> 23
  | (n & 268435456) >> 25
  | (n & 536870912) >> 27
  | (n & 1073741824) >> 29
  | (n & 2147483648) >> 31);
}

inline void bit64_swap(uint64_t& n) CPP_NOEXCEPT
{
  n = static_cast<uint64_t>((n & 1ul) << 63
  | (n & 2ul) << 61
  | (n & 4ul) << 59
  | (n & 8ul) << 57
  | (n & 16ul) << 55
  | (n & 32ul) << 53
  | (n & 64ul) << 51
  | (n & 128ul) << 49
  | (n & 256ul) << 47
  | (n & 512ul) << 45
  | (n & 1024ul) << 43
  | (n & 2048ul) << 41
  | (n & 4096ul) << 39
  | (n & 8192ul) << 37
  | (n & 16384ul) << 35
  | (n & 32768ul) << 33
  | (n & 65536ul) << 31
  | (n & 131072ul) << 29
  | (n & 262144ul) << 27
  | (n & 524288ul) << 25
  | (n & 1048576ul) << 23
  | (n & 2097152ul) << 21
  | (n & 4194304ul) << 19
  | (n & 8388608ul) << 17
  | (n & 16777216ul) << 15
  | (n & 33554432ul) << 13
  | (n & 67108864ul) << 11
  | (n & 134217728ul) << 9
  | (n & 268435456ul) << 7
  | (n & 536870912ul) << 5
  | (n & 1073741824ul) << 3
  | (n & 2147483648ul) << 1
  | (n & 4294967296ul) >> 1
  | (n & 8589934592ul) >> 3
  | (n & 17179869184ul) >> 5
  | (n & 34359738368ul) >> 7
  | (n & 68719476736ul) >> 9
  | (n & 137438953472ul) >> 11
  | (n & 274877906944ul) >> 13
  | (n & 549755813888ul) >> 15
  | (n & 1099511627776ul) >> 17
  | (n & 2199023255552ul) >> 19
  | (n & 4398046511104ul) >> 21
  | (n & 8796093022208ul) >> 23
  | (n & 17592186044416ul) >> 25
  | (n & 35184372088832ul) >> 27
  | (n & 70368744177664ul) >> 29
  | (n & 140737488355328ul) >> 31
  | (n & 281474976710656ul) >> 33
  | (n & 562949953421312ul) >> 35
  | (n & 1125899906842624ul) >> 37
  | (n & 2251799813685248ul) >> 39
  | (n & 4503599627370496ul) >> 41
  | (n & 9007199254740992ul) >> 43
  | (n & 18014398509481984ul) >> 45
  | (n & 36028797018963970ul) >> 47
  | (n & 72057594037927940ul) >> 49
  | (n & 144115188075855870ul) >> 51
  | (n & 288230376151711740ul) >> 53
  | (n & 576460752303423500ul) >> 55
  | (n & 1152921504606847000ul) >> 57
  | (n & 2305843009213694000ul) >> 59
  | (n & 4611686018427388000ul) >> 61
  | (n & 9223372036854776000ul) >> 63);
}

namespace _aux {
  inline char get_char_swap(char c) CPP_NOEXCEPT
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
}

inline void bit_swap(char* n, std::size_t size) CPP_NOEXCEPT
{
  char *end = n + size;
  for (char c; n < end; ++n)
  {
    c = _aux::get_char_swap(*n);
    --end;
    *n = _aux::get_char_swap(*end);
    *end = c;
  }
  if (n != end)
  {
    --n;
    *n = _aux::get_char_swap(*n);
  }
}

namespace _aux {
	template<class T, std::size_t S = bit::size<T>::value>
	struct bit_swap
	{
		inline static void impl(T& bits) CPP_NOEXCEPT
		{ bit_swap(reinterpret_cast<char*>(falcon::addressof(bits)), sizeof(T)); }
	};

#define FALCON_CREATE_BIT_SWAP(S)\
	template<>\
	struct bit_swap<uint##S##_t, S>\
	{\
		inline static void impl(uint##S##_t& bits) CPP_NOEXCEPT\
		{ falcon::bit##S##_swap(bits); }\
	};\
	template<class T>\
	struct bit_swap<T, S>\
	{\
		inline static void impl(T& bits) CPP_NOEXCEPT\
		{ falcon::bit##S##_swap(*reinterpret_cast<uint##S##_t*>(&bits)); }\
	};

	FALCON_CREATE_BIT_SWAP(8)
	FALCON_CREATE_BIT_SWAP(16)
	FALCON_CREATE_BIT_SWAP(32)
	FALCON_CREATE_BIT_SWAP(64)

#undef FALCON_CREATE_BIT_SWAP
}

	template <class T>
	void bit_swap(T& bits) CPP_NOEXCEPT
	{ _aux::bit_swap<T>::impl(bits); }

}

#endif
