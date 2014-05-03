#ifndef FALCON_HELPER_USE_CONST_REVERSE_ITERATOR_HPP
#define FALCON_HELPER_USE_CONST_REVERSE_ITERATOR_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(const_reverse_iterator, use_const_reverse_iterator);
}

template <class T>
struct use_const_reverse_iterator
: _aux::use_const_reverse_iterator<T>
{};

}

#endif
