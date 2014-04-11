#ifndef FALCON_TUPLE_TUPLE_APPLY_HPP
#define FALCON_TUPLE_TUPLE_APPLY_HPP

#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/c++1x/syntax.hpp>

#include <utility>

namespace falcon {

template <typename F, typename Tuple, std::size_t... Indexes>
constexpr CPP1X_DELEGATE_FUNCTION(
  tuple_apply(parameter_index<Indexes...>, F && func, Tuple&& t),
  std::forward<F>(func)(get<Indexes>(std::forward<Tuple>(t))...)
)

template <typename F, typename Tuple, std::size_t... Indexes>
constexpr CPP1X_DELEGATE_FUNCTION(
  tuple_apply(F && func, Tuple&& t),
  tuple_apply(build_tuple_index_t<Tuple>(),
              std::forward<F>(func), std::forward<Tuple>(t)
  )
)

}

#endif
