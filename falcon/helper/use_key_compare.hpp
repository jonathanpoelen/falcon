#ifndef FALCON_HELPER_USE_KEY_COMPARE_HPP
#define FALCON_HELPER_USE_KEY_COMPARE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(key_compare, use_key_compare);
}

template <class T>
struct use_key_compare
: _aux::use_key_compare<T>
{};

}

#endif
