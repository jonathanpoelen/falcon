#ifndef FALCON_MPL_POP_BACK_HPP
#define FALCON_MPL_POP_BACK_HPP

#include <falcon/mpl/pop_back_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence>
struct pop_back
{
  using type = pop_back_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence>::type;
};

}
}

#endif
