#ifndef FALCON_MPL_FIRST_HPP
#define FALCON_MPL_FIRST_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Pair>
struct first
: detail::mpl_apply_def
{ using type = typename Pair::first; };

template<typename Seq>
using first_t = typename first<Seq>::type;

}
}

#endif
