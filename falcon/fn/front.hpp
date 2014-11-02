#ifndef FALCON_FN_FRONT_HPP
#define FALCON_FN_FRONT_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, front)
  using front_fn = adl_::front_fn;
}
}

#endif
