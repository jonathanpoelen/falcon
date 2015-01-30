#ifndef FALCON_STDINT_HPP
#define FALCON_STDINT_HPP

#include <cstdint>

namespace falcon {

inline namespace stdint {

using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;

using std::int_fast8_t;
using std::int_fast16_t;
using std::int_fast32_t;
using std::int_fast64_t;

using std::int_least8_t;
using std::int_least16_t;
using std::int_least32_t;
using std::int_least64_t;

using std::intmax_t;
using std::intptr_t;

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;

using std::uint_fast8_t;
using std::uint_fast16_t;
using std::uint_fast32_t;
using std::uint_fast64_t;

using std::uint_least8_t;
using std::uint_least16_t;
using std::uint_least32_t;
using std::uint_least64_t;

using std::uintmax_t;
using std::uintptr_t;

using std::size_t;
using std::ptrdiff_t;

}

inline namespace stdint_alias {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using imax_t = intmax_t;
using umax_t = uintmax_t;

using iptr_t = intptr_t;
using uptr_t = uintptr_t;

using sz_t = size_t;

using u8p = u8 *;
using cu8p = u8 const *;

}

}

#endif
