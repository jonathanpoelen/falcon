#ifndef FALCON_MPL_INTEGRAL_WRAPPER_HPP
#define FALCON_MPL_INTEGRAL_WRAPPER_HPP

#include <cstddef>

namespace falcon {
namespace mpl {

template<typename T, T N>
struct integral_c
{
  using type = integral_c;
  using value_type = T;
  static const T value = N;
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

struct void_
{
  using type = void_;
};

template<typename T>
struct is_void
: false_
{};

template<>
struct is_void<void_>
: true_
{};

}
}

#endif

