#ifndef FALCON_HELPER_USE_SIZE_TYPE_HPP
#define FALCON_HELPER_USE_SIZE_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(size_type, use_size_type);
}

template <class T>
struct use_size_type
: _aux::use_size_type<T>
{};

}

#endif
