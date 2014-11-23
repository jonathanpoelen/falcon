#ifndef FALCON_FUNCTIONAL_ARGS_HPP
#define FALCON_FUNCTIONAL_ARGS_HPP

#include <falcon/c++1x/syntax.hpp>

#include <tuple>

namespace falcon {

template<std::size_t... Ints>
struct args {
  constexpr args() {}

  template<class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Ts && ... args) const
  , std::make_tuple(std::get<(Ints-1)>(std::forward_as_tuple(args...))...))
};

}

#endif
