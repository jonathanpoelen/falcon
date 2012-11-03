#ifndef FALCON_TYPE_TRAITS_USE_IF_HPP
#define FALCON_TYPE_TRAITS_USE_IF_HPP

#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/use_type.hpp>

namespace falcon
{

/**
 * shorcut notation for eval_if< _T::value, _T, _Default>.
 */
template <typename _T, typename _Default>
struct use_if
: eval_if<_T::value, _T, _Default>
{};

}

#endif