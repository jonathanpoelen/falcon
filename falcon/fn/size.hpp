#ifndef FALCON_FN_SIZE_HPP
#define FALCON_FN_SIZE_HPP

#include <falcon/c++1x/syntax.hpp>
#include <falcon/type_traits/static_const.hpp>

#include <iterator>

namespace falcon {
namespace fn {

namespace adl_ {
  template<class T, std::size_t N>
  constexpr std::size_t size(T const (&)[N]) noexcept
  { return N; }

  template<class T>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    size_cont(T const & x, int)
  , x.size())

  template<class Cont>
  CPP1X_DELEGATE_FUNCTION(
    size_cont(Cont const & cont, unsigned)
  , std::distance(cont.begin(), cont.end()))

  template<class T>
  CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    size(T const & x)
  , size_cont(x, 1))

  struct size_fn
  {
    constexpr size_fn() noexcept {}

    template<class T>
    constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
      operator()(T const & x) const
    , size(x))
  };
}

/// \brief call if possible, non member function size(T), otherwise T::size()
/// If an array is passed, it size is returned.
/// Otherwise std::distance is used
using size_fn = adl_::size_fn;

FALCON_GLOBAL_OBJECT(size, size_fn);

}
}

#endif
