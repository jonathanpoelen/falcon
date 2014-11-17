#ifndef FALCON_FN_EMPLACE_BACK_HPP
#define FALCON_FN_EMPLACE_BACK_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(adl_, emplace_back)
  using emplace_back_fn = adl_::emplace_back_fn;
}
}

#endif
