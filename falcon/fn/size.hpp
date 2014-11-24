#ifndef FALCON_FN_SIZE_HPP
#define FALCON_FN_SIZE_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  namespace adl_ {
    template<class T, std::size_t N>
    constexpr std::size_t size(T const (&)[N]) noexcept
    { return N; }
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, size)
  /// \brief call if possible, non member function size(T), otherwise T::size()
  /// If an array is passed, it size is returned.
  using size_fn = adl_::size_fn;
}
}

#endif
