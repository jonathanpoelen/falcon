#ifndef FALCON_FN_POP_FRONT_HPP
#define FALCON_FN_POP_FRONT_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/fn/make_global_function_object.hpp>

namespace falcon {
namespace fn {

/// \brief call T::pop_front()
struct pop_front_fn {
  constexpr pop_front_fn() noexcept {}

  template<class T>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(T && x) const
  , x.pop_front())
};

FALCON_GLOBAL_OBJECT(pop_front, pop_front_fn);

}
}

#endif
