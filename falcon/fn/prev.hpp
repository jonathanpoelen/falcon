#ifndef FALCON_FN_PREV_HPP
#define FALCON_FN_PREV_HPP

#include <falcon/fn/make_global_function_object.hpp>

#include <iterator>

namespace falcon {
namespace fn {

/// \brief call T::prev() or std::prev(T, n) if T is a iterator type
struct prev_fn {
  constexpr prev_fn() noexcept {}

  template<class T>
  constexpr auto operator()(T && x) const
  noexcept(noexcept(x.prev()))
  -> decltype(x.prev())
  { return x.prev() ; }

  template<class It>
  constexpr It operator()(
    It it, typename std::iterator_traits<It>::difference_type = 1) const
  { return std::prev(it) ; }
};

FALCON_GLOBAL_OBJECT(prev, prev_fn);

}
}

#endif
