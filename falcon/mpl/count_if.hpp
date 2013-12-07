#ifndef FALCON_MPL_COUNT_IF_HPP
#define FALCON_MPL_COUNT_IF_HPP

#include <falcon/mpl/aux_/count_if_impl.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <falcon/mpl/apply.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename Pred>
struct count_if
{
private:
  template<typename U>
  using predicate = apply_t<Pred, U>;

public:
  using type = typename aux::count_if_impl<
    begin_t<Sequence>
  , end_t<Sequence>
  , predicate
  >::type;

  const static decltype(type::value) value = type::value;
};

template<typename Sequence, typename Pred>
using count_if_t = typename count_if<Sequence, Pred>::type;

}
}

#endif
