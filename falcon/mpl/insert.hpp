#ifndef FALCON_MPL_INSERT_HPP
#define FALCON_MPL_INSERT_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename Pos, typename T = detail::na>
struct insert
: detail::mpl_apply_def
{ using type = typename aux::insert<detail::sequence_t<Seq>, Pos, T>::type; };

template<typename Seq, typename Pos, typename T = detail::na>
using insert_t = typename insert<Seq, Pos, T>::type;

}
}

#endif
