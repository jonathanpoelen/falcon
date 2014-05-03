#ifndef FALCON_HELPER_USE_VALUE_COMPARE_HPP
#define FALCON_HELPER_USE_VALUE_COMPARE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(value_compare, use_value_compare);
}

template <class T>
struct use_value_compare
: _aux::use_value_compare<T>
{};

}

#endif
