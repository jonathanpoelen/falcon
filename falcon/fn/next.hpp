#ifndef FALCON_FN_NEXT_HPP
#define FALCON_FN_NEXT_HPP

#include <falcon/fn/make_global_function_object.hpp>

#include <iterator>

namespace falcon {
namespace fn {

/// \brief call T::next() or std::next(T, n) if T is a iterator type
struct next_fn {
  constexpr next_fn() noexcept {}

  template<class T>
  constexpr auto operator()(T && x) const
  noexcept(noexcept(x.next()))
  -> decltype(x.next())
  { return x.next() ; }

  template<class It>
  constexpr It operator()(
    It it, typename std::iterator_traits<It>::difference_type = 1) const
  { return std::next(it) ; }
};

FALCON_GLOBAL_OBJECT(next, next_fn);

}
}

#endif
