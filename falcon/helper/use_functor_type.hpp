#ifndef FALCON_HELPER_USE_FUNCTOR_TYPE_HPP
#define FALCON_HELPER_USE_FUNCTOR_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(functor_type, use_functor_type);
}

template <class T>
struct use_functor_type
: _aux::use_functor_type<T>
{};

}

#endif
