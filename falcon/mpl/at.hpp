#ifndef FALCON_MPL_AT_HPP
#define FALCON_MPL_AT_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, typename Pos, typename Default = void_>
struct at
: detail::mpl_apply_def
{ using type = typename aux::at<detail::sequence_t<Seq>, Pos, Default>::type; };

}
}

#endif
