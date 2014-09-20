#ifndef TUPLE_IS_TUPLE_LIKE_HPP
#define TUPLE_IS_TUPLE_LIKE_HPP

#include <type_traits>
#include <utility>
#include <tuple>
#include <array>

namespace falcon {

template<typename T>
struct is_tuple_like
: std::false_type
{};
template<typename... Elements>
struct is_tuple_like<std::tuple<Elements...>>
: std::true_type
{};
template<typename T, std::size_t N>
struct is_tuple_like<std::array<T, N>>
: std::true_type
{};
template<typename T, typename U>
struct is_tuple_like<std::pair<T, U>>
: std::true_type
{};

}

#endif
