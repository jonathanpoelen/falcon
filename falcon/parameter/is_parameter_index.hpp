#ifndef FALCON_PARAMETER_IS_PARAMETER_INDEX_HPP
#define FALCON_PARAMETER_IS_PARAMETER_INDEX_HPP

#include <falcon/parameter/parameter_index.hpp>
#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename _Indexes>
struct is_parameter_index
: false_type
{};

template<std::size_t... _Indexes>
struct is_parameter_index<parameter_index<_Indexes...>>
: true_type
{};

}

#endif