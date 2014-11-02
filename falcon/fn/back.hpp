#ifndef FALCON_FN_BACK_HPP
#define FALCON_FN_BACK_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, back)
  using back_fn = adl_::back_fn;
}
}

#endif
