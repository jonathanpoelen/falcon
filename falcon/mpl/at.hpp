#ifndef FALCON_MPL_AT_HPP
#define FALCON_MPL_AT_HPP

#include <falcon/mpl/at_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename N>
struct at
{
  using type = typename at_impl<sequence_tag_t<Sequence>>
  ::template apply<Sequence, N>::type;
};

template<typename Sequence, std::size_t N>
struct at_c
{
  using type = typename at_impl<sequence_tag_t<Sequence>>
  ::template apply<Sequence, ulong_<N>>::type;
};

template<typename Sequence, typename N>
using at_t = typename at<Sequence, N>::type;

template<typename Sequence, std::size_t N>
using at_c_t = typename at_c<Sequence, N>::type;

}
}

#endif
