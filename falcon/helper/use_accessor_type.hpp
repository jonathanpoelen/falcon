#ifndef FALCON_HELPER_USE_ACCESSOR_TYPE_HPP
#define FALCON_HELPER_USE_ACCESSOR_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(accessor_type, __use_accessor_type);

template <class T>
struct use_accessor_type
: __use_accessor_type<T>
{};

}

#endif
