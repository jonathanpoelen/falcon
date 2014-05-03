#ifndef FALCON_HELPER_USE_VALUE_TYPE_HPP
#define FALCON_HELPER_USE_VALUE_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(value_type, use_value_type);
}

template <class T>
struct use_value_type
: _aux::use_value_type<T>
{};

}

#endif
