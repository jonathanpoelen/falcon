#ifndef FALCON_FN_DATA_HPP
#define FALCON_FN_DATA_HPP

#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {
  namespace adl_ {
    template<class T, std::size_t N>
    constexpr T const * data(T const (&arr)[N]) noexcept
    { return arr; }

    template<class T, std::size_t N>
    T * data(T (&arr)[N]) noexcept
    { return arr; }
  }

  FALCON_MAKE_GLOBAL_FUNCTION_OBJECT(adl_, data)
  /// \brief call if possible, non member function data(T), otherwise T::data()
  /// If an array is passed, a pointer is returned.
  typedef adl_::data_fn data_fn;
}
}

#endif
