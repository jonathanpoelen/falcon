#ifndef FALCON_HELPER_USE_ARGUMENT_TYPE_HPP
#define FALCON_HELPER_USE_ARGUMENT_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(argument_type, __use_argument_type);

template <class T>
struct use_argument_type
: __use_argument_type<T>
{};

}

#endif
