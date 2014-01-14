#ifndef FALCON_HELPER_USE_KEY_TYPE_HPP
#define FALCON_HELPER_USE_KEY_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(key_type, __use_key_type);

template <class T>
struct use_key_type
: __use_key_type<T>
{};

}

#endif
