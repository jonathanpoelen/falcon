#ifndef FALCON_FN_POP_BACK_HPP
#define FALCON_FN_POP_BACK_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {

/// \brief call T::pop_back()
struct pop_back_fn {
  constexpr pop_back_fn() noexcept {}

  template<class T>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x) const
  , x.pop_back())
};

FALCON_GLOBAL_OBJECT(pop_back, pop_back_fn);

}
}

#endif
