#ifndef FALCON_FN_LENGTH_HPP
#define FALCON_FN_LENGTH_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  namespace adl_ {
    template<class T>
    constexpr std::size_t length(T const * p) noexcept
    {
      const T * s = p;
      while (*s) ++s;
      return std::size_t(s-p);
    }
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, length)
  /// \brief call if possible, non member function length(T), otherwise T::length()
  /// If an array or a pointer is passed, a size_t is returned.
  typedef adl_::length_fn length_fn;
}
}

#endif
