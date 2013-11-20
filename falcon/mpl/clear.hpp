#ifndef FALCON_MPL_CLEAR_HPP
#define FALCON_MPL_CLEAR_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct clear
: detail::mpl_apply_def
{ using type = typename aux::clear<detail::sequence_t<Seq>>::type; };

template<typename Seq>
using clear_t = typename clear<Seq>::type;

}
}

#endif
