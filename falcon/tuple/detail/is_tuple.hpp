#ifndef TUPLE_DETAIL_ISTUPLE_HPP
#define TUPLE_DETAIL_ISTUPLE_HPP

#include <type_traits>
#include <falcon/tuple/detail/tuplefwd.hpp>

namespace std
{
  template<typename, std::size_t>
  class array;
  template<typename, typename>
  class pair;
}

namespace falcon {

namespace detail {
template<typename>
struct is_tuple
: std::false_type
{};
template<typename... Elements>
struct is_tuple<std::tuple<Elements...>>
: std::true_type
{};

template<typename T>
struct is_tuple_impl
: std::false_type
{};
template<typename... Elements>
struct is_tuple_impl<std::tuple<Elements...>>
: std::true_type
{};
template<typename T, std::size_t N>
struct is_tuple_impl<std::array<T, N>>
: std::true_type
{};
template<typename T, typename U>
struct is_tuple_impl<std::pair<T, U>>
: std::true_type
{};
}

template<typename T>
struct is_tuple
: ::falcon::detail::is_tuple<typename std::remove_cv<T>::type>
{};

template<typename T>
struct is_tuple_impl
: ::falcon::detail::is_tuple_impl<typename std::remove_cv<T>::type>
{};

}

#endif
