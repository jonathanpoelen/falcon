#ifndef FALCON_FN_DATA_HPP
#define FALCON_FN_DATA_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  namespace adl_ {
    template<class T>
    constexpr T * data(T * p) noexcept
    { return p; }
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, data)
  /// \brief call if possible, non member function data(T), otherwise T::data()
  /// If an array or a pointer is passed, a pointer is returned.
  typedef adl_::data_fn data_fn;
}
}

#endif
