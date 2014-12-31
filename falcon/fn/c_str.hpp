#ifndef FALCON_FN_C_STR_HPP
#define FALCON_FN_C_STR_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  namespace adl_ {
    template<class T>
    constexpr T * c_str(T * p) noexcept
    { return p; }
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, c_str)
  /// \brief call if possible, non member function c_str(T), otherwise T::c_str()
  /// If an array or a pointer is passed, a pointer is returned.
  typedef adl_::c_str_fn c_str_fn;
}
}

#endif
