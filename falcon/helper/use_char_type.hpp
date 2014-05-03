#ifndef FALCON_HELPER_USE_CHAR_TYPE_HPP
#define FALCON_HELPER_USE_CHAR_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(char_type, use_char_type);
}

template <class T>
struct use_char_type
: _aux::use_char_type<T>
{};

}

#endif
