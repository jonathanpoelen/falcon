#ifndef FALCON_MPL_SIZE_HPP
#define FALCON_MPL_SIZE_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct size
: detail::mpl_apply_def
{
  static const std::size_t value = aux::size<detail::sequence_t<Seq>>::value;
  using type = integral_c<std::size_t, value>;
};

template<typename Seq>
using size_t = size<Seq>;

}
}

#endif
