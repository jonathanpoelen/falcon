#ifndef FALCON_TYPE_TRAITS_USE_IF_HPP
#define FALCON_TYPE_TRAITS_USE_IF_HPP

#include <falcon/type_traits/eval_if.hpp>

namespace falcon
{

/**
 * shorcut notation for eval_if< T::value, T, Default>.
 */
template <typename T, typename Default>
struct use_if
: eval_if<T::value, T, Default>
{};

template<class T, typename Default>
using use_if_t = typename use_if<T, Default>::type;

}

#endif
