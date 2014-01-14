#ifndef FALCON_HELPER_USE_ITERATOR_CATEGORY_HPP
#define FALCON_HELPER_USE_ITERATOR_CATEGORY_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

FALCON_USE_XXX_TRAIT_NAMED_DEF(iterator_category, __use_iterator_category);

template <class T>
struct use_iterator_category
: __use_iterator_category<T>
{};

}

#endif
