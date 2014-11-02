#ifndef FALCON_FN_EMPTY_HPP
#define FALCON_FN_EMPTY_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_RESULT(bool, adl_, empty)
  using empty_fn = adl_::empty_fn;
}
}

#endif
