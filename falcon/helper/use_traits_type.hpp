#ifndef FALCON_HELPER_USE_TRAITS_TYPE_HPP
#define FALCON_HELPER_USE_TRAITS_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(traits_type, use_traits_type);
}

template <class T>
struct use_traits_type
: _aux::use_traits_type<T>
{};

}

#endif
