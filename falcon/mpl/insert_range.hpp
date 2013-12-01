#ifndef FALCON_MPL_INSERT_RANGE_HPP
#define FALCON_MPL_INSERT_RANGE_HPP

#include <falcon/mpl/insert_range_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename Pos, typename Range>
struct insert_range
{
  using type = insert_range_impl<sequence_tag_t<Sequence>>
  ::template apply<Sequence, Pos, Range>::type;
};

}
}

#endif
