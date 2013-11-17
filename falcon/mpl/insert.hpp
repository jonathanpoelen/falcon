#ifndef FALCON_MPL_INSERT_HPP
#define FALCON_MPL_INSERT_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename Pos, typename T>
struct insert
: detail::mpl_apply_def
{ using type = typename aux::insert<detail::sequence_t<Seq>, Pos, T>::type; };

}
}

#endif
