#ifndef FALCON_HELPER_USE_CONST_REFERENCE_HPP
#define FALCON_HELPER_USE_CONST_REFERENCE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(const_reference, __use_const_reference);

template <class T>
struct use_const_reference
: __use_const_reference<T>
{};

}

#endif
