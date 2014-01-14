#ifndef FALCON_HELPER_USE_OFF_TYPE_HPP
#define FALCON_HELPER_USE_OFF_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(off_type, __use_off_type);

template <class T>
struct use_off_type
: __use_off_type<T>
{};

}

#endif
