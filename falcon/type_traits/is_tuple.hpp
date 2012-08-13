#ifndef _FALCON_TYPE_TRAITS_IS_TUPLE_HPP
#define _FALCON_TYPE_TRAITS_IS_TUPLE_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <cstddef>

namespace std {
template<typename...>
class tuple;
template<typename, std::size_t>
class array;
}

namespace falcon {

template<typename>
struct is_tuple
: false_type
{};

template<typename _T, std::size_t N>
struct is_tuple<std::array<_T, N> >
: public true_type
{};

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename... _Args>
struct is_tuple<std::tuple<_Args...> >
: public true_type
{};
#endif

}

#endif
