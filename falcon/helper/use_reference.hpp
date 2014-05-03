#ifndef FALCON_HELPER_USE_REFERENCE_HPP
#define FALCON_HELPER_USE_REFERENCE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(reference, use_reference);
}

template <class T>
struct use_reference
: _aux::use_reference<T>
{};

}

#endif
