#ifndef FALCON_HELPER_USE_ALLOCATOR_TYPE_HPP
#define FALCON_HELPER_USE_ALLOCATOR_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(allocator_type, use_allocator_type);
}

template <class T>
struct use_allocator_type
: _aux::use_allocator_type<T>
{};

}

#endif
