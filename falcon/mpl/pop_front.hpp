#ifndef FALCON_MPL_POP_FRONT_HPP
#define FALCON_MPL_POP_FRONT_HPP

#include <falcon/mpl/pop_front_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence>
struct pop_front
{
  using type = pop_front_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence>::type;
};

}
}

#endif
