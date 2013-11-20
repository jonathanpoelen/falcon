#ifndef FALCON_MPL_PUSH_BACK_HPP
#define FALCON_MPL_PUSH_BACK_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename T>
struct push_back
: detail::mpl_apply_def
{ using type = typename aux::push_back<detail::sequence_t<Seq>, T>::type; };

template<typename Seq, typename T>
using push_back_t = typename push_back<Seq, T>::type;

}
}

#endif
