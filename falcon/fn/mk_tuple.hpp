#ifndef FALCON_FN_MK_TUPLE_HPP
#define FALCON_FN_MK_TUPLE_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/c++1x/syntax.hpp>

#include <tuple>

namespace falcon {
namespace fn {

struct mk_tuple_fn {
  constexpr mk_tuple_fn() noexcept {}

  template<class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Ts && ... es) const
  , std::make_tuple(std::forward<Ts>(es)...))
};

struct forward_as_tuple_fn {
  constexpr forward_as_tuple_fn() noexcept {}

  template<class... Ts>
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(Ts && ... es) const
  , std::forward_as_tuple(std::forward<Ts>(es)...))
};

using make_tuple_fn = mk_tuple_fn;

FALCON_GLOBAL_OBJECT(mk_tuple, mk_tuple_fn);
FALCON_GLOBAL_OBJECT(forward_as_tuple, forward_as_tuple_fn);

}
}

#endif
