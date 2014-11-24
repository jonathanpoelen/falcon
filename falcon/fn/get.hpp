#ifndef FALCON_FN_GET_HPP
#define FALCON_FN_GET_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(adl_, get)
  /// \brief call if possible, non member function get(T, args...), otherwise T::get(args...)
  typedef adl_::get_fn get_fn;
}
}

#endif
