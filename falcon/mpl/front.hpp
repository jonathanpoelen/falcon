#ifndef FALCON_MPL_FRONT_HPP
#define FALCON_MPL_FRONT_HPP

#include <falcon/mpl/front_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename First, typename Last>
struct front
{
  using type = front_impl<sequence_tag_t<Sequence>>
    ::template apply< Sequence,First,Last >::type;
};

}
}

#endif
