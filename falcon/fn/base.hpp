#ifndef FALCON_FN_BASE_HPP
#define FALCON_FN_BASE_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

namespace falcon {
namespace fn {

/// \brief call T::base()
struct base_fn {
  constexpr base_fn() noexcept {}

  template<class T>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
  operator()(T && x) const
  , x.base())
};

FALCON_GLOBAL_OBJECT(base, base_fn);

}
}

#endif
