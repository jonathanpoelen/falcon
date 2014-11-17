#ifndef FALCON_FN_EMPLACE_HPP
#define FALCON_FN_EMPLACE_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(adl_, emplace)
  using emplace_fn = adl_::emplace_fn;
}
}

#endif
