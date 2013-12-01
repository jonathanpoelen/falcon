#ifndef FALCON_MPL_PUSH_FRONT_HPP
#define FALCON_MPL_PUSH_FRONT_HPP

#include <falcon/mpl/push_front_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename T>
struct push_front
{
  using type = push_front_impl<sequence_tag_t<Sequence>>
  ::template apply< Sequence,T >::type;
};

}
}

#endif
