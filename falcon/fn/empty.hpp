#ifndef FALCON_FN_EMPTY_HPP
#define FALCON_FN_EMPTY_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  namespace adl_ {
    template<class T, std::size_t N>
    constexpr std::size_t empty(T const (&)[N]) noexcept
    { return false; }
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_RESULT(bool, adl_, empty)
  using empty_fn = adl_::empty_fn;
}
}

#endif
