#ifndef FALCON_MPL_IS_SEQUENCE_HPP
#define FALCON_MPL_IS_SEQUENCE_HPP

#include <falcon/mpl/detail/fwd.hpp
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct is_sequence
: detail::mpl_apply_def
{
  static const bool value = detail::is_mpl_sequence<Seq>(1);
  using type = integral_c<bool, value>;
};

template<typename Seq>
using is_sequence_t = typename is_sequence<Seq>::type;

}
}

#endif
