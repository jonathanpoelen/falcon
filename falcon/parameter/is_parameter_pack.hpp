#ifndef FALCON_PARAMETER_IS_PARAMETER_PACK_HPP
#define FALCON_PARAMETER_IS_PARAMETER_PACK_HPP

#include <falcon/parameter/parameter_pack.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename T>
struct is_parameter_pack
: false_type
{};

template<typename... Elements>
struct is_parameter_pack<parameter_pack<Elements...>>
: true_type
{};

namespace paramter {
  template<typename T>
  using is_pack = is_parameter_pack<T>;
}

}

#endif
