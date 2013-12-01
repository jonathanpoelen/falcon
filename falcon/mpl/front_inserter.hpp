#ifndef FALCON_MPL_FRONT_INSERTER_HPP
#define FALCON_MPL_FRONT_INSERTER_HPP

#include <falcon/mpl/push_front.hpp>
#include <falcon/mpl/inserter.hpp>
#include <falcon/mpl/arg.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence>
using front_inserter = inserter<Sequence, push_front<arg<1>, arg<2>>>;

}}

#endif
