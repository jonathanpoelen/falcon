#ifndef FALCON_MPL_MAX_ELEMENT_HPP
#define FALCON_MPL_MAX_ELEMENT_HPP

#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/less.hpp>
#include <falcon/mpl/apply.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/mpl/aux_/min_element_impl.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename Pred = less<arg<1>,arg<2>>>
struct max_element
{
private:
  struct predicate
  {
    template<typename Iter, typename Iter2>
    using apply = apply_t<Pred, Iter2, Iter>;
  };

public:
  using type = typename aux::min_element_impl<
    begin_t<Sequence>
  , end_t<Sequence>
  , predicate
  >::type;
};

template<typename Sequence, typename Pred = less<arg<1>,arg<2>>>
using max_element_t = typename max_element<Sequence, Pred>::type;

}
}

#endif
