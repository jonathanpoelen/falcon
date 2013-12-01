#ifndef FALCON_MPL_BACK_INSERTER_HPP
#define FALCON_MPL_BACK_INSERTER_HPP

#include <falcon/mpl/push_back.hpp>
#include <falcon/mpl/inserter.hpp>
#include <falcon/mpl/arg.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence>
using back_inserter = inserter<Sequence, push_back<arg<1>, arg<2>>>;

}}

#endif
