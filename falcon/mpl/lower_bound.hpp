#ifndef FALCON_MPL_LOWER_BOUND_HPP
#define FALCON_MPL_LOWER_BOUND_HPP

#include <falcon/mpl/aux_/find_if_impl.hpp>
#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/less.hpp>
#include <falcon/mpl/apply.hpp>
#include <falcon/mpl/begin_end.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename T, typename Pred = less<arg<1>,arg<2>>>
struct lower_bound
{
private:
  template<typename U>
  using predicate = bool_<!apply_t<Pred, U, T>::value>;

public:
  using type = typename aux::find_if_impl<
    begin_t<Sequence>
  , end_t<Sequence>
  , predicate
  >::type;
};

template<typename Sequence, typename T, typename Pred = less<arg<1>,arg<2>>>
using lower_bound_t = typename lower_bound<Sequence, T, Pred>::type;

}
}

#endif
