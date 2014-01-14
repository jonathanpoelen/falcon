#ifndef FALCON_HELPER_USE_ITERATOR_HPP
#define FALCON_HELPER_USE_ITERATOR_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(iterator, __use_iterator);

template <class T>
struct use_iterator
: __use_iterator<T>
{};

}

#endif
