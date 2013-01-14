#ifndef FALCON_TYPE_TRAITS_AND_HPP
#define FALCON_TYPE_TRAITS_AND_HPP

#include <type_traits>

namespace falcon {

template<bool... Values>
struct and_
: std::false_type
{};

template<>
struct and_<true>
: std::true_type
{};

template<bool... Values>
struct and_<true, Values...>
: and_<Values...>
{};

template<typename... Values>
struct and_c
: and_<Values::value...>
{};

}

#endif