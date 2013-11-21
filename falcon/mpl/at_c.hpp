#ifndef FALCON_MPL_AT_C_HPP
#define FALCON_MPL_AT_C_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename Seq, long Pos>
struct at_c
: detail::mpl_apply_def
{ using type = typename aux::at<detail::sequence_t<Seq>, long_<Pos>>::type; };

template<typename Seq, typename Pos>
using at_c_t = typename at_c<Seq, Pos>::type;



}
}

#endif
