#ifndef FALCON_HELPER_USE_ITERATOR_TYPE_HPP
#define FALCON_HELPER_USE_ITERATOR_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(iterator_type, use_iterator_type);
}

template <class T>
struct use_iterator_type
: _aux::use_iterator_type<T>
{};

}

#endif
