#ifndef FALCON_MPL_SECOND_HPP
#define FALCON_MPL_SECOND_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Pair>
struct second
: detail::mpl_apply_def
{ using type = typename Pair::second; };

template<typename Seq>
using second_t = typename second<Seq>::type;

}
}

#endif
