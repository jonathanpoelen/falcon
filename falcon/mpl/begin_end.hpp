#ifndef FALCON_MPL_BEGIN_END_HPP
#define FALCON_MPL_BEGIN_END_HPP

#include <falcon/mpl/sequence_tag.hpp>
#include <falcon/mpl/begin_end_fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence>
struct begin
{
  using type = typename begin_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence>::type;
};

template<typename Sequence>
struct end
{
  using type = typename end_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence>::type;
};

template<typename Sequence>
using begin_t = typename begin<Sequence>::type;

template<typename Sequence>
using end_t = typename end<Sequence>::type;

}
}

#endif
