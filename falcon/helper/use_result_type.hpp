#ifndef FALCON_HELPER_USE_RESULT_TYPE_HPP
#define FALCON_HELPER_USE_RESULT_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon {

namespace _aux {
FALCON_USE_XXX_TRAIT_NAMED_DEF(result_type, use_result_type);
}

template <class T>
struct use_result_type
: _aux::use_result_type<T>
{};

}

#endif
