#ifndef FALCON_TUPLE_ARRAY_COMPATIBILITY_HPP
#define FALCON_TUPLE_ARRAY_COMPATIBILITY_HPP

#include <array>
#include <utility>

namespace falcon {

template<std::size_t I, typename T, std::size_t N>
T& get(T (&a)[N]) noexcept
{
  static_assert(I < N, "index is out of bounds");
  return a[I];
}

template<std::size_t I, typename T, std::size_t N>
constexpr T&& get(T (&&a)[N]) noexcept
{
  static_assert(I < N, "index is out of bounds");
  return std::forward<T>(a[I]);
}

template<std::size_t I, typename T, std::size_t N>
constexpr const T& get(const T (&a)[N]) noexcept
{
  static_assert(I < N, "index is out of bounds");
  return a[I];
}

}

namespace std {

template<typename T, std::size_t N>
struct tuple_size<T[N]>
: public integral_constant<std::size_t, N>
{};

template<std::size_t I, typename T, std::size_t N>
struct tuple_element<I, T[N]>
{ typedef T type; };

}

#endif
