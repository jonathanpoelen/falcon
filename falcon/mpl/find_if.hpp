#ifndef FALCON_MPL_FIND_IF_HPP
#define FALCON_MPL_FIND_IF_HPP

#include <falcon/mpl/aux_/find_if_impl.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/mpl/apply.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename Pred>
struct find_if
{
private:
  template<typename U>
  using predicate = apply_t<Pred, U>;

public:
  using type = typename aux::find_if_impl<
    begin_t<Sequence>
  , end_t<Sequence>
  , predicate
  >::type;
};

template<typename Sequence, typename Pred>
using find_if_t = typename find_if<Sequence, Pred>::type;

}
}

#endif
