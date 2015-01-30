#ifndef FALCON_FN_ITER_SWAP_HPP
#define FALCON_FN_ITER_SWAP_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/c++1x/syntax.hpp>

#include <algorithm>

namespace falcon {
namespace fn {

/// \brief call std::iter_swap(it1, it2)
struct iter_swap_fn {
  constexpr iter_swap_fn() noexcept {}

  template<class It1, class It2>
  void operator()(It1 && a, It2 && b) const
  { std::iter_swap(std::forward<It1>(a), std::forward<It2>(b)); }
};

FALCON_GLOBAL_OBJECT(iter_swap, iter_swap_fn);

}
}

#endif
