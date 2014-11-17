#ifndef FALCON_FN_INSERT_HPP
#define FALCON_FN_INSERT_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(adl_, insert)
  using insert_fn = adl_::insert_fn;
}
}

#endif
