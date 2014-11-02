#ifndef FALCON_FN_NEXT_HPP
#define FALCON_FN_NEXT_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, next)
  using next_fn = adl_::next_fn;
}
}

#endif
