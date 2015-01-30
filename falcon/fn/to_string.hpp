#ifndef FALCON_FN_TO_STRING_HPP
#define FALCON_FN_TO_STRING_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/fn/make_global_function_object.hpp>

#include <string>

namespace falcon {
namespace fn {
  namespace adl_ {
    using std::to_string;
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, to_string)
  /// \brief call if possible, member function T::to_string(), otherwise to_string(T)
  typedef adl_::to_string_fn to_string_fn;
}
}

#endif
