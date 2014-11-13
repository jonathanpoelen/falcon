#ifndef FALCON_HELPER_USE_IS_TRANSPARENT_HPP
#define FALCON_HELPER_USE_IS_TRANSPARENT_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(is_transparent, use_is_transparent);
}

template <class T>
struct use_argument_type
: _aux::use_is_transparent<T>
{};

}

#endif
