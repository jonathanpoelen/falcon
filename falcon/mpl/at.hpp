#ifndef FALCON_MPL_AT_HPP
#define FALCON_MPL_AT_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename Pos>
struct at
: detail::mpl_apply_def
{ using type = typename aux::at<detail::sequence_t<Seq>, Pos>::type; };

}
}

#endif
