#ifndef FALCON_FUNCTIONAL_ARGS_HPP
#define FALCON_FUNCTIONAL_ARGS_HPP

#include <falcon/type_traits/normalize_index.hpp>
#include <falcon/functional/arg.hpp>
#include <falcon/c++1x/syntax.hpp>

#include <tuple>


namespace falcon {

/// \brief wrapper for std::forward_as_tuple(arg< Indexes>(args...)...)
template<unormalized_index_t... Indexes>
struct args {
  constexpr args() noexcept {}

  template<class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Ts&&... args) const
  , std::forward_as_tuple(arg<
    (normalize_index<Indexes, sizeof...(args)>::value)
  >(std::forward<Ts>(args)...)...))
};

}

#endif
