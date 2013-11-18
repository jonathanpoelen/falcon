#ifndef FALCON_MPL_ERASE_HPP
#define FALCON_MPL_ERASE_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename Pos, typename Last = detail::na>
struct erase<vector<Ts...>, Pos, Last>
: detail::mpl_apply_def
{ using type = typename aux::erase_impl<detail::sequence_t<Seq>, Pos, Last>::type; };

}
}

#endif
