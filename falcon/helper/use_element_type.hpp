#ifndef FALCON_HELPER_USE_ELEMENT_TYPE_HPP
#define FALCON_HELPER_USE_ELEMENT_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(element_type, __use_element_type);

template <class T>
struct use_element_type
: __use_element_type<T>
{};

}

#endif
