#ifndef FALCON_HELPER_USE_CONST_ITERATOR_HPP
#define FALCON_HELPER_USE_CONST_ITERATOR_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(const_iterator, __use_const_iterator);

template <class T>
struct use_const_iterator
: __use_const_iterator<T>
{};

}

#endif
