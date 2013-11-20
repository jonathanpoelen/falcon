#ifndef FALCON_MPL_ERASE_HPP
#define FALCON_MPL_ERASE_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename Pos, typename Last = detail::na>
struct erase
: detail::mpl_apply_def
{ using type = typename aux::erase<detail::sequence_t<Seq>, Pos, Last>::type; };

template<typename Seq, typename Pos, typename Last = detail::na>
using erase_t = typename erase<Seq, Pos, Last>::type;

}
}

#endif
