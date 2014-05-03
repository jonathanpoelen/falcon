#ifndef FALCON_HELPER_USE_CONST_REFERENCE_HPP
#define FALCON_HELPER_USE_CONST_REFERENCE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(const_reference, use_const_reference);
}

template <class T>
struct use_const_reference
: _aux::use_const_reference<T>
{};

}

#endif
