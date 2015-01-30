#ifndef FALCON_TYPE_TRAITS_IS_NATIVE_HPP
#define FALCON_TYPE_TRAITS_IS_NATIVE_HPP

#include <cstdint>
#include <type_traits>

namespace falcon {

#define MAKE_IS_XXX_NAMED(type, name) \
  template<class T> using is_##name = std::is_same<T, type>

#define MAKE_IS_XXX(type) MAKE_IS_XXX_NAMED(type, type)

MAKE_IS_XXX(void);
MAKE_IS_XXX(bool);
MAKE_IS_XXX(char);
MAKE_IS_XXX(short);
MAKE_IS_XXX(int);
MAKE_IS_XXX(unsigned);
MAKE_IS_XXX(long);
MAKE_IS_XXX(float);
MAKE_IS_XXX(double);

MAKE_IS_XXX_NAMED(signed char, signed_char);
MAKE_IS_XXX_NAMED(signed char, schar);
MAKE_IS_XXX_NAMED(unsigned char, unsigned_char);
MAKE_IS_XXX_NAMED(unsigned char, uchar);
MAKE_IS_XXX_NAMED(unsigned, uint);
MAKE_IS_XXX_NAMED(unsigned long, unsigned_long);
MAKE_IS_XXX_NAMED(unsigned long, ulong);
MAKE_IS_XXX_NAMED(long long, long_long);
MAKE_IS_XXX_NAMED(long long, llong);
MAKE_IS_XXX_NAMED(unsigned long long, unsigned_long_long);
MAKE_IS_XXX_NAMED(unsigned long long, ulong_long);
MAKE_IS_XXX_NAMED(unsigned long long, ullong);
MAKE_IS_XXX_NAMED(long double, long_double);
MAKE_IS_XXX_NAMED(long double, ldouble);


MAKE_IS_XXX(wchar_t);
MAKE_IS_XXX(char16_t);
MAKE_IS_XXX(char32_t);

MAKE_IS_XXX_NAMED(wchar_t, wchar);
MAKE_IS_XXX_NAMED(char16_t, char16);
MAKE_IS_XXX_NAMED(char32_t, char32);


MAKE_IS_XXX_NAMED(decltype(nullptr), nullptr);

MAKE_IS_XXX_NAMED(char *, charp);
MAKE_IS_XXX_NAMED(char const *, const_charp);
MAKE_IS_XXX_NAMED(char const *, ccharp);
MAKE_IS_XXX_NAMED(unsigned char *, u8p);
MAKE_IS_XXX_NAMED(unsigned char *, ucharp);
MAKE_IS_XXX_NAMED(unsigned char const *, const_u8p);
MAKE_IS_XXX_NAMED(unsigned char const *, cu8p);
MAKE_IS_XXX_NAMED(unsigned char const *, const_ucharp);
MAKE_IS_XXX_NAMED(unsigned char const *, cucharp);
MAKE_IS_XXX_NAMED(void *, voidp);
MAKE_IS_XXX_NAMED(void const *, const_voidp);
MAKE_IS_XXX_NAMED(void const *, cvoidp);


MAKE_IS_XXX_NAMED(std::int8_t, int8);
MAKE_IS_XXX_NAMED(std::int16_t, int16);
MAKE_IS_XXX_NAMED(std::int32_t, int32);
MAKE_IS_XXX_NAMED(std::int64_t, int64);
MAKE_IS_XXX_NAMED(std::int_fast8_t, int_fast8);
MAKE_IS_XXX_NAMED(std::int_fast16_t, int_fast16);
MAKE_IS_XXX_NAMED(std::int_fast32_t, int_fast32);
MAKE_IS_XXX_NAMED(std::int_fast64_t, int_fast64);
MAKE_IS_XXX_NAMED(std::int_least8_t, int_least8);
MAKE_IS_XXX_NAMED(std::int_least16_t, int_least16);
MAKE_IS_XXX_NAMED(std::int_least32_t, int_least32);
MAKE_IS_XXX_NAMED(std::int_least64_t, int_least64);

MAKE_IS_XXX_NAMED(std::intmax_t, intmax);
MAKE_IS_XXX_NAMED(std::intptr_t, intptr);

MAKE_IS_XXX_NAMED(std::int8_t, i8);
MAKE_IS_XXX_NAMED(std::int16_t, i16);
MAKE_IS_XXX_NAMED(std::int32_t, i32);
MAKE_IS_XXX_NAMED(std::int64_t, i64);
MAKE_IS_XXX_NAMED(std::int_fast8_t, fast8);
MAKE_IS_XXX_NAMED(std::int_fast16_t, fast16);
MAKE_IS_XXX_NAMED(std::int_fast32_t, fast32);
MAKE_IS_XXX_NAMED(std::int_fast64_t, fast64);
MAKE_IS_XXX_NAMED(std::int_least8_t, least8);
MAKE_IS_XXX_NAMED(std::int_least16_t, least16);
MAKE_IS_XXX_NAMED(std::int_least32_t, least32);
MAKE_IS_XXX_NAMED(std::int_least64_t, least64);

MAKE_IS_XXX_NAMED(std::intmax_t, imax);
MAKE_IS_XXX_NAMED(std::intptr_t, iptr);

MAKE_IS_XXX_NAMED(std::uint8_t, uint8);
MAKE_IS_XXX_NAMED(std::uint16_t, uint16);
MAKE_IS_XXX_NAMED(std::uint32_t, uint32);
MAKE_IS_XXX_NAMED(std::uint64_t, uint64);
MAKE_IS_XXX_NAMED(std::uint_fast8_t, uint_fast8);
MAKE_IS_XXX_NAMED(std::uint_fast16_t, uint_fast16);
MAKE_IS_XXX_NAMED(std::uint_fast32_t, uint_fast32);
MAKE_IS_XXX_NAMED(std::uint_fast64_t, uint_fast64);
MAKE_IS_XXX_NAMED(std::uint_least8_t, uint_least8);
MAKE_IS_XXX_NAMED(std::uint_least16_t, uint_least16);
MAKE_IS_XXX_NAMED(std::uint_least32_t, uint_least32);
MAKE_IS_XXX_NAMED(std::uint_least64_t, uint_least64);

MAKE_IS_XXX_NAMED(std::uintmax_t, uintmax);
MAKE_IS_XXX_NAMED(std::uintptr_t, uintptr);

MAKE_IS_XXX_NAMED(std::uint8_t, u8);
MAKE_IS_XXX_NAMED(std::uint16_t, u16);
MAKE_IS_XXX_NAMED(std::uint32_t, u32);
MAKE_IS_XXX_NAMED(std::uint64_t, u64);
MAKE_IS_XXX_NAMED(std::uint_fast8_t, ufast8);
MAKE_IS_XXX_NAMED(std::uint_fast16_t, ufast16);
MAKE_IS_XXX_NAMED(std::uint_fast32_t, ufast32);
MAKE_IS_XXX_NAMED(std::uint_fast64_t, ufast64);
MAKE_IS_XXX_NAMED(std::uint_least8_t, uleast8);
MAKE_IS_XXX_NAMED(std::uint_least16_t, uleast16);
MAKE_IS_XXX_NAMED(std::uint_least32_t, uleast32);
MAKE_IS_XXX_NAMED(std::uint_least64_t, uleast64);

MAKE_IS_XXX_NAMED(std::uintmax_t, umax);
MAKE_IS_XXX_NAMED(std::uintptr_t, uptr);


MAKE_IS_XXX_NAMED(std::size_t, size_t);
MAKE_IS_XXX_NAMED(std::size_t, sz_t);
MAKE_IS_XXX_NAMED(std::ptrdiff_t, ptrdiff_t);
MAKE_IS_XXX_NAMED(std::ptrdiff_t, ptrdiff);

#undef MAKE_IS_XXX
#undef MAKE_IS_XXX_NAMED

}

#endif
