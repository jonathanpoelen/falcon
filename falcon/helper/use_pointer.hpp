#ifndef FALCON_HELPER_USE_POINTER_HPP
#define FALCON_HELPER_USE_POINTER_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(pointer, __use_pointer);

template <class T>
struct use_pointer
: __use_pointer<T>
{};

}

#endif
