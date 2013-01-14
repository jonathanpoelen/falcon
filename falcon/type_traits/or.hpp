#ifndef FALCON_TYPE_TRAITS_OR_HPP
#define FALCON_TYPE_TRAITS_OR_HPP

#include <type_traits>

namespace falcon {

template<bool... Values>
struct or_
: std::false_type
{};

template<bool... Values>
struct or_<false, Values...>
: or_<Values...>
{};

template<bool... Values>
struct or_<true, Values...>
: std::true_type
{};

template<typename... Values>
struct or_c
: or_<Values::value...>
{};

}

#endif