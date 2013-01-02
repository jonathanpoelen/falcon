#ifndef FALCON_TYPE_TRAITS_DISABLE_IF_HPP
#define FALCON_TYPE_TRAITS_DISABLE_IF_HPP

#include <falcon/type_traits/enable_if.hpp>

namespace falcon {

template<bool C, typename _Tp = void>
struct disable_if
: enable_if<!C, _Tp>
{};

template<class C, typename _Tp = void>
struct disable_if_c
: enable_if<!C::value, _Tp>
{};

}

#endif