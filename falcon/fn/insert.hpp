#ifndef FALCON_FN_INSERT_HPP
#define FALCON_FN_INSERT_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_ARGS(
    adl_, insert, (class U), (U&& arg), (std::forward<U>(arg)))
  using insert_fn = adl_::insert_fn;
}
}

#endif
