#ifndef FALCON_PARAMETER_IS_PARAMETER_PACK_HPP
#define FALCON_PARAMETER_IS_PARAMETER_PACK_HPP

#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename _Elements>
struct is_parameter_pack
: false_type
{};

template<typename... _Elements>
struct is_parameter_pack<parameter_pack<_Elements...>>
: true_type
{};

}

#endif