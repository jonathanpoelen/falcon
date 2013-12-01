#ifndef FALCON_MPL_CLEAR_HPP
#define FALCON_MPL_CLEAR_HPP

#include <falcon/mpl/sequence_tag.hpp>
#include <falcon/mpl/clear_fwd.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence>
struct clear
{
  using type = clear_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence>::type;
};

template<typename Sequence>
using clear_t = typename clear<Sequence>::type;

}
}
