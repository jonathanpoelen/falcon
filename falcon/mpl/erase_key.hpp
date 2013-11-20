#ifndef FALCON_MPL_ERASE_KEY_HPP
#define FALCON_MPL_ERASE_KEY_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename Pos>
struct erase_key
: detail::mpl_apply_def
{ using type = typename aux::erase_key<detail::sequence_t<Seq>, Pos>::type; };

template<typename Seq, typename Pos>
using erase_key_t = typename erase_key<Seq, Pos>::type;

}
}

#endif
