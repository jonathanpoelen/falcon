#ifndef FALCON_HELPER_USE_FIRST_ARGUMENT_TYPE_HPP
#define FALCON_HELPER_USE_FIRST_ARGUMENT_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(first_argument_type, __use_first_argument_type);

template <class T>
struct use_first_argument_type
: __use_first_argument_type<T>
{};

}

#endif
