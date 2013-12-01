#ifndef FALCON_MPL_INTEGRAL_C_HPP
#define FALCON_MPL_INTEGRAL_C_HPP

#include <cstddef>
#include <falcon/mpl/advance_fwd.hpp>

namespace falcon {
namespace mpl {

struct integral_c_tag {};

template<typename T, T N>
struct integral_c
{
  using type = integral_c;
  using value_type = T;
  static const T value = N;
  constexpr operator bool() const
  { return this->value; }

  using tag = integral_c_tag;

  using next = integral_c<T, N+1>;
  using prior = integral_c<T, N-1>;
};

template<>
struct advance_impl<integral_c_tag>
{
  template<typename Integral, typename N>
  struct apply
  { using type = integral_c<typename Integral::type, Integral::value + N::value>; };

  template<bool val, typename N>
  class apply<integral_c<bool, val>, N>
  {};
};

template<bool c>
using bool_ = integral_c<bool, c>;

using false_ = std::false_type;
using true_ = std::true_type;

template<char N>
using char_ = integral_c<char, N>;

template<unsigned char N>
using uchar_ = integral_c<unsigned char, N>;

template<signed char N>
using schar_ = integral_c<signed char, N>;

template<short N>
using short_ = integral_c<short, N>;

template<unsigned short N>
using ushort_ = integral_c<unsigned short, N>;

template<int N>
using int_ = integral_c<int, N>;

template<unsigned int N>
using uint_ = integral_c<unsigned int, N>;

template<long N>
using long_ = integral_c<long, N>;

template<unsigned long N>
using ulong_ = integral_c<unsigned long, N>;

template<long long N>
using llong_ = integral_c<long long, N>;

template<unsigned long long N>
using ullong_ = integral_c<unsigned long long, N>;

}
}

#endif

