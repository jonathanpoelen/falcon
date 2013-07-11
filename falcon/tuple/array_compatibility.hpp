#ifndef FALCON_TUPLE_ARRAY_COMPATIBILITY_HPP
#define FALCON_TUPLE_ARRAY_COMPATIBILITY_HPP

#include <falcon/tuple/detail/is_tuple.hpp>
#include <utility>

namespace std {

template<std::size_t I, typename T, std::size_t N>
T& get(T (&a)[N]) noexcept
{ return a[I]; }

template<std::size_t I, typename T, std::size_t N>
constexpr T&& get(T (&&a)[N]) noexcept
{ return std::forward<T>(a[I]); }

template<std::size_t I, typename T, std::size_t N>
constexpr const T& get(const T (&a)[N]) noexcept
{ return a[I]; }

template<typename T, std::size_t N>
struct tuple_size<T[N]>
: public integral_constant<std::size_t, N>
{};

template<std::size_t I, typename T, std::size_t N>
struct tuple_element<I, T[N]>
{ typedef T type; };

}

namespace falcon {

template<typename _T, std::size_t _N>
struct is_tuple_impl<_T[_N]>
: std::true_type
{};

}

#endif
