#ifndef FALCON_BIT_BIT_SWAP_HPP
#define FALCON_BIT_BIT_SWAP_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/bit/size.hpp>
#include <falcon/memory/addressof.hpp>

namespace falcon {

inline void b8swap(uint8_t& n) CPP_NOEXCEPT
{
  n = static_cast<uint8_t>(
    (n & 1) << 7
  | (n & 2) << 5
  | (n & 4) << 3
  | (n & 8) << 1
  | (n & 16) >> 1
  | (n & 32) >> 3
  | (n & 64) >> 5
  | (n & 128) >> 7);
}

inline void b16swap(uint16_t& n) CPP_NOEXCEPT
{
  n = static_cast<uint16_t>(
    (n & 1) << 15
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

inline void b32swap(uint32_t& n) CPP_NOEXCEPT
{
  n = static_cast<uint32_t>(
    (n & 1) << 31
  | (n & uint32_t(2ul)) << 29
  | (n & uint32_t(4ul)) << 27
  | (n & uint32_t(8ul)) << 25
  | (n & uint32_t(16ul)) << 23
  | (n & uint32_t(32ul)) << 21
  | (n & uint32_t(64ul)) << 19
  | (n & uint32_t(128ul)) << 17
  | (n & uint32_t(256ul)) << 15
  | (n & uint32_t(512ul)) << 13
  | (n & uint32_t(1024ul)) << 11
  | (n & uint32_t(2048ul)) << 9
  | (n & uint32_t(4096ul)) << 7
  | (n & uint32_t(8192ul)) << 5
  | (n & uint32_t(16384ul)) << 3
  | (n & uint32_t(32768ul)) << 1
  | (n & uint32_t(65536ul)) >> 1
  | (n & uint32_t(131072ul)) >> 3
  | (n & uint32_t(262144ul)) >> 5
  | (n & uint32_t(524288ul)) >> 7
  | (n & uint32_t(1048576ul)) >> 9
  | (n & uint32_t(2097152ul)) >> 11
  | (n & uint32_t(4194304ul)) >> 13
  | (n & uint32_t(8388608ul)) >> 15
  | (n & uint32_t(16777216ul)) >> 17
  | (n & uint32_t(33554432ul)) >> 19
  | (n & uint32_t(67108864ul)) >> 21
  | (n & uint32_t(134217728ul)) >> 23
  | (n & uint32_t(268435456ul)) >> 25
  | (n & uint32_t(536870912ul)) >> 27
  | (n & uint32_t(1073741824ul)) >> 29
  | (n & uint32_t(2147483648ul)) >> 31);
}

inline void b64swap(uint64_t& n) CPP_NOEXCEPT
{
  n = static_cast<uint64_t>(
    (n & 1ul) << 63
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
  inline unsigned char get_char_swap(unsigned char c) CPP_NOEXCEPT
	{
		return static_cast<unsigned char>(
      (c & 1) << 7
		| (c & 2) << 5
		| (c & 4) << 3
		| (c & 8) << 1
		| (c & 16) >> 1
		| (c & 32) >> 3
		| (c & 64) >> 5
		| (c & 128) >> 7);
	}
}

inline void bswap(void * p, std::size_t size) CPP_NOEXCEPT
{
  unsigned char *n = static_cast<unsigned char*>(p);
  unsigned char *end = n + size;
  for (unsigned char c; n < end; ++n)
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
	struct bswap
	{
		inline static void impl(T& bits) CPP_NOEXCEPT
		{ bswap(reinterpret_cast<char*>(falcon::addressof(bits)), sizeof(T)); }
	};

#define FALCON_CREATE_BIT_SWAP(S)\
	template<>\
	struct bswap<uint##S##_t, S>\
	{\
		inline static void impl(uint##S##_t& bits) CPP_NOEXCEPT\
		{ falcon::bit##S##_swap(bits); }\
	};\
	template<class T>\
	struct bswap<T, S>\
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
void bswap(T& bits) CPP_NOEXCEPT
{ _aux::bswap<T>::impl(bits); }

}

#endif
