#ifndef FALCON_MPL_COUNT_HPP
#define FALCON_MPL_COUNT_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename T>
struct count
: detail::mpl_apply_def
{
  static const std::size_t value = aux::count<detail::sequence_t<Seq>, T>::value;
  using type = integral_c<std::size_t, value>;
};

}
}

#endif
