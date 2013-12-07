#ifndef FALCON_MPL_FIND_HPP
#define FALCON_MPL_FIND_HPP

#include <falcon/mpl/aux_/find_if_impl.hpp>
#include <falcon/mpl/begin_end.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {

template<typename Sequence, typename T>
struct find
{
private:
  template<typename U>
  using predicate = std::is_same<T, U>;

public:
  using type = typename aux::find_if_impl<
    begin_t<Sequence>
  , end_t<Sequence>
  , predicate
  >::type;
};

template<typename Sequence, typename T>
using find_t = typename find<Sequence, T>::type;

}
}

#endif
