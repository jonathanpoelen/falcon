#ifndef FALCON_FN_BASE_HPP
#define FALCON_FN_BASE_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, base)
  using base_fn = adl_::base_fn;
}
}

#endif
