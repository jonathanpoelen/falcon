#ifndef FALCON_HELPER_USE_INT_TYPE_HPP
#define FALCON_HELPER_USE_INT_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(int_type, __use_int_type);

template <class T>
struct use_int_type
: __use_int_type<T>
{};

}

#endif
