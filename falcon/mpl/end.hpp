#ifndef FALCON_MPL_END_HPP
#define FALCON_MPL_END_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct end
: detail::mpl_apply_def
{ using type = typename aux::end<detail::sequence_t<Seq>>::type; };

template<typename Seq>
using end_t = typename end<Seq>::type;

}
}

#endif
