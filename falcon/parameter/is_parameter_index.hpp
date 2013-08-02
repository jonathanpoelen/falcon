#ifndef FALCON_PARAMETER_IS_PARAMETER_INDEX_HPP
#define FALCON_PARAMETER_IS_PARAMETER_INDEX_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename T>
struct is_parameter_index
: false_type
{};

template<std::size_t... Indexes>
struct is_parameter_index<parameter_index<Indexes...>>
: true_type
{};

namespace parameter {
  template<typename T>
  using is_index = is_parameter_index<T>;
}

}

#endif
