#ifndef FALCON_FN_INSERT_AFTER_HPP
#define FALCON_FN_INSERT_AFTER_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(adl_, insert_after)
  using insert_after_fn = adl_::insert_after_fn;
}
}

#endif
