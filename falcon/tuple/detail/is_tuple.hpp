#ifndef _TUPLE_DETAIL_IS_TUPLE_HPP
#define _TUPLE_DETAIL_IS_TUPLE_HPP

#include <tuple>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename>
struct __is_tuple
: falcon::false_type
{};

template<typename... _Elements>
struct __is_tuple<std::tuple<_Elements...>>
: falcon::true_type
{};

}

#endif