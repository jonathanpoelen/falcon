#ifndef FALCON_TUPLE_TUPLE_APPLY_HPP
#define FALCON_TUPLE_TUPLE_APPLY_HPP

#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/c++1x/syntax.hpp>

#include <utility>

namespace falcon {

constexpr struct tuple_apply_t {
  template <typename Function, typename Tuple, std::size_t... Indexes>
  constexpr
  CPP1X_DELEGATE_FUNCTION(operator()(parameter_index<Indexes...>, Function && func, Tuple&& t) const,
                          std::forward<Function>(func)(get<Indexes>(std::forward<Tuple>(t))...))

  template <typename Function, typename Tuple, std::size_t... Indexes>
  constexpr
  CPP1X_DELEGATE_FUNCTION(operator()(Function && func, Tuple&& t) const,
                          operator()(build_tuple_index_t<typename std::decay<Tuple>::type>(),
                                      std::forward<Function>(func), std::forward<Tuple>(t)))
} tuple_apply;

}

#endif
