#ifndef FALCON_MPL_BACK_HPP
#define FALCON_MPL_BACK_HPP

#include <falcon/mpl/back_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence>
struct back
{
  using type = back_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence>::type;
};

template<typename Sequence>
using back_t = typename back<Sequence>::type;

}
}

#endif
