#ifndef FALCON_LITERAL_BITSET_HPP
#define FALCON_LITERAL_BITSET_HPP

#include <falcon/literal/detail/literal_support.hpp>

namespace std {
  template<std::size_t>
  class bitset;
}

namespace falcon {
namespace literal {
namespace bitset {

template<char... Bits>
struct __check_bits
{ static const bool valid = false; };

template<char High, char... Bits>
struct __check_bits<High, Bits...>
{ static const bool valid = (High == '0' || High == '1') && __check_bits<Bits...>::valid; };

template<>
struct __check_bits<>
{ static const bool valid = true; };

template<char... Bits>
inline constexpr std::bitset<sizeof...(Bits)> operator "" _bits()
{
  static_assert(__check_bits<Bits...>::valid, "invalid digit in binary string");
  return std::bitset<sizeof...(Bits)>((const char []){Bits...}, sizeof...(Bits));
}

}
}
}

#endif
