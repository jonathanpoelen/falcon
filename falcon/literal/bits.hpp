#ifndef FALCON_LITERAL_BITS_HPP
#define FALCON_LITERAL_BITS_HPP

#include <falcon/literal/utility.hpp>

namespace falcon {
namespace literal {
namespace bits {

	template<typename _To, _To val, char... chars>
	class __to_val_bit;

	template<typename _To, _To val>
	struct __to_val_bit<_To, val>
	: std::integral_constant<_To, val>
	{};

	template<typename _To, _To val, char c, char... chars>
	struct __to_val_bit<_To, val, c, chars...>
	{
		static_assert((c == '0' || c == '1'), "invalid digit in binary string");
		static const _To value = __to_val_bit<_To, __to_value<_To, (val << 1) + (c=='0'?0:1) >::__value, chars...>::value;
	};

#define FALCON_USER_DEFINED_STDINT_LITERAL(type, s)\
	template<char... chars>\
	constexpr type operator "" _##s##b() noexcept\
	{ return __to_val_bit<type, 0, chars...>::value; }

	FALCON_USER_DEFINED_STDINT_LITERAL(char, char)
	FALCON_USER_DEFINED_STDINT_LITERAL(short, short)
	FALCON_USER_DEFINED_STDINT_LITERAL(int, )
	FALCON_USER_DEFINED_STDINT_LITERAL(long, l)
	FALCON_USER_DEFINED_STDINT_LITERAL(long long, ll)
	FALCON_USER_DEFINED_STDINT_LITERAL(unsigned char, uchar)
	FALCON_USER_DEFINED_STDINT_LITERAL(unsigned short, ushort)
	FALCON_USER_DEFINED_STDINT_LITERAL(unsigned int, u)
	FALCON_USER_DEFINED_STDINT_LITERAL(unsigned long, ul)
	FALCON_USER_DEFINED_STDINT_LITERAL(unsigned long long, ull)

#undef FALCON_USER_DEFINED_STDINT_LITERAL

}}}

#endif