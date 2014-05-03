#ifndef FALCON_HELPER_USE_POS_TYPE_HPP
#define FALCON_HELPER_USE_POS_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(pos_type, use_pos_type);
}

template <class T>
struct use_pos_type
: _aux::use_pos_type<T>
{};

}

#endif
