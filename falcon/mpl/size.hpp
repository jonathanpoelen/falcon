#ifndef FALCON_MPL_SIZE_HPP
#define FALCON_MPL_SIZE_HPP

#include <falcon/mpl/size_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence>
struct size
{
  using type = typename size_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence>;
  const static decltype(type::value) value = type::value;
};

template<typename Sequence>
using size_t = size<Sequence>;

}
}

#endif
