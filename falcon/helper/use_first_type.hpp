#ifndef FALCON_HELPER_USE_FIRST_TYPE_HPP
#define FALCON_HELPER_USE_FIRST_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(first_type, use_first_type);
}

template <class T>
struct use_first_type
: _aux::use_first_type<T>
{};

}

#endif
