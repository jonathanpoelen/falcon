#ifndef FALCON_FN_GET_HPP
#define FALCON_FN_GET_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, get)
  using get_fn = adl_::get_fn;
}
}

#endif
