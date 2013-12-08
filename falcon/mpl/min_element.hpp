#ifndef FALCON_MPL_MIN_ELEMENT_HPP
#define FALCON_MPL_MIN_ELEMENT_HPP

#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/less.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/mpl/aux_/min_element_impl.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename Pred = less<arg<1>,arg<2>>>
struct min_element
{
  using type = typename aux::min_element_impl<
    begin_t<Sequence>
  , end_t<Sequence>
  , Pred
  >::type;
};

template<typename Sequence, typename Pred = less<arg<1>,arg<2>>>
using min_element_t = typename min_element<Sequence, Pred>::type;

}
}

#endif
