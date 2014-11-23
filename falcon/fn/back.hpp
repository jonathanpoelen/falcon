#ifndef FALCON_FN_BACK_HPP
#define FALCON_FN_BACK_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  namespace adl_ {
    template<class T, std::size_t N>
    constexpr T const & back(T const (&arr)[N]) noexcept
    { return arr[N-1]; }

    template<class T, std::size_t N>
    T & back(T (&arr)[N]) noexcept
    { return arr[N-1]; }
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, back)
  using back_fn = adl_::back_fn;
}
}

#endif
