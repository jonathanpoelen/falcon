#ifndef FALCON_MPL_HAS_KEY_HPP
#define FALCON_MPL_HAS_KEY_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename T>
struct has_key
: detail::mpl_apply_def
{
  static const bool value = aux::has_key<detail::sequence_t<Seq>, T>::value;
  using type = integral_c<bool, value>;
};

template<typename Seq, typename T>
using has_key_t = typename has_key<Seq, T>::type;

}
}

#endif
