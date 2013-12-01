#ifndef FALCON_MPL_PUSH_BACK_HPP
#define FALCON_MPL_PUSH_BACK_HPP

#include <falcon/mpl/push_back_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename T>
struct push_back
{
  using type = typename push_back_impl<sequence_tag_t<Sequence>>
    ::template apply< Sequence,T >::type;
};

template<typename Sequence, typename T>
using push_back_t = typename push_back<Sequence, T>::type;

}
}

#endif
