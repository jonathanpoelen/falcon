#ifndef FALCON_MPL_POP_FRONT_HPP
#define FALCON_MPL_POP_FRONT_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct pop_front
: detail::mpl_apply_def
{ using type = typename aux::pop_front<detail::sequence_t<Seq>>::type; };

}
}

#endif
