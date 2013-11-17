#ifndef FALCON_MPL_POP_BACK_HPP
#define FALCON_MPL_POP_BACK_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct pop_back
: detail::mpl_apply_def
{ using type = typename aux::pop_back<detail::sequence_t<Seq>>::type; };

}
}

#endif
