#ifndef FALCON_FN_AT_HPP
#define FALCON_FN_AT_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, at)
  using at_fn = adl_::at_fn;
}
}

#endif
