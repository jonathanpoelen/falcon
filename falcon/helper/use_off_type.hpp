#ifndef FALCON_HELPER_USE_OFF_TYPE_HPP
#define FALCON_HELPER_USE_OFF_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(off_type, use_off_type);
}

template <class T>
struct use_off_type
: _aux::use_off_type<T>
{};

}

#endif
