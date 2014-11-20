#ifndef FALCON_FN_DATA_HPP
#define FALCON_FN_DATA_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, data)
  using data_fn = adl_::data_fn;
}
}

#endif
