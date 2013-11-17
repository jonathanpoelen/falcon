#ifndef FALCON_MPL_BEGIN_HPP
#define FALCON_MPL_BEGIN_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Seq>
struct begin
: detail::mpl_apply_def
{ using type = typename aux::begin<detail::sequence_t<Seq>>::type; };

}
}

#endif
