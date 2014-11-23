#ifndef FALCON_FN_FRONT_HPP
#define FALCON_FN_FRONT_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  namespace adl_ {
    template<class T, std::size_t N>
    constexpr T const & front(T const (&arr)[N]) noexcept
    { return arr[0]; }

    template<class T, std::size_t N>
    T & front(T (&arr)[N]) noexcept
    { return arr[0]; }
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, front)
  using front_fn = adl_::front_fn;
}
}

#endif
