#ifndef FALCON_TYPE_TRAITS_USE_DEFAULT_HPP
#define FALCON_TYPE_TRAITS_USE_DEFAULT_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

struct use_default;

template<typename T>
struct is_default
: false_type
{};

template<>
struct is_default<use_default>
: true_type
{};

}

#endif
