#ifndef FALCON_TYPE_TRAITS_NORMALIZE_ARGUMENT_HPP
#define FALCON_TYPE_TRAITS_NORMALIZE_ARGUMENT_HPP

#include <falcon/type_traits/normalize_index.hpp>

namespace falcon {

///\brief if @a I less to 0, value = @a I + @a Nm + 1, otherwise value = @a I.
template<unormalized_index_t I, std::size_t Nm>
struct normalize_argument
: std::integral_constant<
  std::size_t
, (normalize_index<I, Nm>::value + (I < 0))>
{};

}

#endif
