#ifndef FALCON_MPL_COPY_IF_HPP
#define FALCON_MPL_COPY_IF_HPP

#include <falcon/mpl/arg.hpp>
#include <falcon/mpl/fold.hpp>
#include <falcon/mpl/eval_if.hpp>
#include <falcon/mpl/identity.hpp>
#include <falcon/mpl/back_inserter.hpp>

namespace falcon {
namespace mpl {

/// TODO is map/set ?
template<typename Sequence, typename Pred, typename In = back_inserter<Sequence>>
struct copy_if
{
  using type = typename fold<
    Sequence
  , typename In::state
  , eval_if<
      apply<Pred, arg<2>>
    , apply<typename In::operation, arg<1>, arg<2>>
    , identity<arg<1>>
    >
  >::type::type;
};

template<typename Sequence, typename Pred, typename In = back_inserter<Sequence>>
using copy_if_t = typename copy_if<Sequence, Pred, In>::type;

}
}

#endif
