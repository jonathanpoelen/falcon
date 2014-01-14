#ifndef FALCON_HELPER_USE_DIFFERENCE_TYPE_HPP
#define FALCON_HELPER_USE_DIFFERENCE_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(difference_type, __use_difference_type);

template <class T>
struct use_difference_type
: __use_difference_type<T>
{};

}

#endif
