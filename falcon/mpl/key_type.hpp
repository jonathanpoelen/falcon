#ifndef FALCON_MPL_KEY_TYPE_HPP
#define FALCON_MPL_KEY_TYPE_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename T>
struct key_type
: detail::mpl_apply_def
{ using type = typename aux::key_type<detail::sequence_t<Seq>, T>::type; };

template<typename Seq, typename T>
using key_type_t = typename key_type<Seq, T>::type;

}
}

#endif
