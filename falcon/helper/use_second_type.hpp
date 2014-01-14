#ifndef FALCON_HELPER_USE_SECOND_TYPE_HPP
#define FALCON_HELPER_USE_SECOND_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(second_type, __use_second_type);

template <class T>
struct use_second_type
: __use_second_type<T>
{};

}

#endif
