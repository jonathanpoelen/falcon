#ifndef FALCON_MPL_BACK_HPP
#define FALCON_MPL_BACK_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct back
: detail::mpl_apply_def
{ using type = typename aux::back<detail::sequence_t<Seq>>; };

template<typename Seq>
using back_t = typename back<Seq>::type;

}
}

#endif
