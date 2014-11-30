#ifndef FALCON_FN_EMPTY_HPP
#define FALCON_FN_EMPTY_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

#include <cstddef>

namespace falcon {
namespace fn {

namespace adl_ {
  template<class T, std::size_t N>
  constexpr bool
  empty(T const (&)[N]) noexcept
  { return N; }

  template<class T>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    empty_cont(T const & x, int)
  , x.empty())

  template<class Cont>
  CPP1X_DELEGATE_FUNCTION(
    empty_cont(Cont const & cont, unsigned)
  , cont.begin() == cont.end())

  template<class T>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    empty(T const & x)
  , empty_cont(x, 1))

  struct empty_fn
  {
    constexpr empty_fn() noexcept {}

    template<class T>
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
      operator()(T const & x) const
    , empty(x))
  };
}

/// \brief call T::empty()
/// If an array is passed, the last element is returned.
typedef adl_::empty_fn empty_fn;

FALCON_GLOBAL_OBJECT(empty, empty_fn);

}
}

#endif
