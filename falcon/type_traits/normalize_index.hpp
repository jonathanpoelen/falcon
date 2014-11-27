#ifndef FALCON_TYPE_TRAITS_NORMALIZE_INDEX_HPP
#define FALCON_TYPE_TRAITS_NORMALIZE_INDEX_HPP

#include <falcon/config.hpp>

#include <type_traits>

namespace falcon {

#ifdef IN_IDE_PARSER
using unormalized_index_t = long long;
#else
using unormalized_index_t = long long;
// using unormalized_index_t = std::make_signed<std::size_t>::type;
#endif

///\brief if @a I less to 0, value = @a I + @a Nm, otherwise value = @a I.
template<unormalized_index_t I, std::size_t Nm>
struct normalize_index
: std::integral_constant<
  std::size_t
, ((I < 0) ? Nm - std::size_t(-I) : std::size_t(I))>
{
  static_assert(Nm != 0, "Nm is 0");
  static_assert(I < 0 ? std::size_t(-I) <= Nm : 1, "I < 0 && -I > Nm");
};

}

#endif
