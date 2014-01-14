#ifndef FALCON_HELPER_USE_TYPE_HPP
#define FALCON_HELPER_USE_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(type, __use_type);

template <class T>
struct use_type
: __use_type<T>
{};

}

#endif
