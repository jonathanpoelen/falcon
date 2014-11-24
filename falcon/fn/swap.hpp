#ifndef FALCON_FN_SWAP_HPP
#define FALCON_FN_SWAP_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/utility/swap.hpp>

namespace falcon {
namespace fn {

/// \brief call if possible, non member function swap(T, T), otherwise std::swap(T, T)
struct swap_fn {
  constexpr swap_fn() noexcept {}

  template<class T>
  void operator()(T & a, T & b) const
  { ::falcon_swap_impl::swap_impl(a, b); }
};

FALCON_GLOBAL_OBJECT(swap, swap_fn);

}
}

#endif
