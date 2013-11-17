#ifndef FALCON_MPL_INSERT_RANGE_HPP
#define FALCON_MPL_INSERT_RANGE_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename Pos, typename Range>
struct insert_range
: detail::mpl_apply_def
{ using type = typename aux::insert_range<detail::sequence_t<Seq>, Pos, Range>::type; };

}
}

#endif
