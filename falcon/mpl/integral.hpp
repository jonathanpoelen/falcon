#ifndef FALCON_MPL_INTEGRAL_WRAPPER_HPP
#define FALCON_MPL_INTEGRAL_WRAPPER_HPP

#include <type_traits>

namespace falcon {
namespace mpl {

template<typename T, T N>
using integral_c = std::integral_constant<T, N>;

template<bool c>
using bool_ = std::integral_constant<bool, c>;

using false_ = std::false_type;
using true_ = std::true_type;

template<char N>
using char_ = std::integral_constant<char, N>;

template<unsigned char N>
using uchar_ = std::integral_constant<unsigned char, N>;

template<signed char N>
using schar_ = std::integral_constant<signed char, N>;

template<short N>
using short_ = std::integral_constant<short, N>;

template<unsigned short N>
using ushort_ = std::integral_constant<unsigned short, N>;

template<int N>
using int_ = std::integral_constant<int, N>;

template<unsigned int N>
using uint_ = std::integral_constant<unsigned int, N>;

template<long N>
using long_ = std::integral_constant<long, N>;

template<unsigned long N>
using ulong_ = std::integral_constant<unsigned long, N>;

template<long long N>
using llong_ = std::integral_constant<long long, N>;

template<unsigned long long N>
using ullong_ = std::integral_constant<unsigned long long, N>;

template<std::size_t N>
using size_t = std::integral_constant<std::size_t, N>;

struct void_
{
  typedef void_ type;
};

template<typename T>
struct is_void
: std::false_type
{};

template<>
struct is_void<void_>
: std::true_type
{};

}
}

#endif

