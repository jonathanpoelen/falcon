#ifndef FALCON_FN_POP_FRONT_HPP
#define FALCON_FN_POP_FRONT_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, pop_front)
  using pop_front_fn = adl_::pop_front_fn;
}
}

#endif
