#ifndef FALCON_FN_EXCHANGE_HPP
#define FALCON_FN_EXCHANGE_HPP

#include <falcon/utility/exchange.hpp>>
#include <falcon/type_traits/static_const.hpp>


namespace falcon {
namespace fn {

/// \brief call std::exchange(x)
struct exchange_fn {
  constexpr exchange_fn() noexcept {}

  template <typename T, typename U = T>
  T exchange(T & obj, U && new_val)
  { return ::falcon::exchange(obj, std::forward<U>(new_val)); }
};

FALCON_GLOBAL_OBJECT(exchange, exchange_fn);

}
}

#endif
