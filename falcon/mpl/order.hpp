#ifndef FALCON_MPL_ORDER_HPP
#define FALCON_MPL_ORDER_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename T>
struct order
: detail::mpl_apply_def
{
  static const std::size_t value = aux::order<detail::sequence_t<Seq>, T>::value;
  using type = integral_c<std::size_t, value>;
};

template<typename Seq, typename T>
using order_t = typename order<Seq, T>::type;

}
}

#endif
