#ifndef FALCON_HELPER_USE_COMPARE_TYPE_HPP
#define FALCON_HELPER_USE_COMPARE_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(compare_type, __use_compare_type);

template <class T>
struct use_compare_type
: __use_compare_type<T>
{};

}

#endif
