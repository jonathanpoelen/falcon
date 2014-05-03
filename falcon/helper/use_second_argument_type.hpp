#ifndef FALCON_HELPER_USE_SECOND_ARGUMENT_TYPE_HPP
#define FALCON_HELPER_USE_SECOND_ARGUMENT_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(second_argument_type, use_second_argument_type);
}

template <class T>
struct use_second_argument_type
: _aux::use_second_argument_type<T>
{};

}

#endif
