#ifndef FALCON_MPL_EMPTY_HPP
#define FALCON_MPL_EMPTY_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct empty
: detail::mpl_apply_def
{
  static const bool value = aux::empty<detail::sequence_t<Seq>>::value;
  using type = integral_c<bool, value>;
};

template<typename Seq>
using empty_t = empty<Seq>;

}
}

#endif
