#ifndef FALCON_FN_POP_BACK_HPP
#define FALCON_FN_POP_BACK_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, pop_back)
  using pop_back_fn = adl_::pop_back_fn;
}
}

#endif
