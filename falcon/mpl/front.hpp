#ifndef FALCON_MPL_FRONT_HPP
#define FALCON_MPL_FRONT_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct front
: detail::mpl_apply_def
{ using type = typename aux::front<detail::sequence_t<Seq>>; };

}
}

#endif
