#ifndef FALCON_MPL_PUSH_FRONT_HPP
#define FALCON_MPL_PUSH_FRONT_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename T>
struct push_front
: detail::mpl_apply_def
{ using type = typename aux::push_front<detail::sequence_t<Seq>, T>::type; };

template<typename Seq, typename T>
using push_front_t = typename push_front<Seq, T>::type;

}
}

#endif
