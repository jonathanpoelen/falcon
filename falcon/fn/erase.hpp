#ifndef FALCON_FN_ERASE_HPP
#define FALCON_FN_ERASE_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(adl_, erase)
  using erase_fn = adl_::erase_fn;
}
}

#endif
