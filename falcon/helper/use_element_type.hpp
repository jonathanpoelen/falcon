#ifndef FALCON_HELPER_USE_ELEMENT_TYPE_HPP
#define FALCON_HELPER_USE_ELEMENT_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(element_type, use_element_type);
}

template <class T>
struct use_element_type
: _aux::use_element_type<T>
{};

}

#endif
