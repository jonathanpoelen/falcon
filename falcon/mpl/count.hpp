#ifndef FALCON_MPL_COUNT_HPP
#define FALCON_MPL_COUNT_HPP

#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename T>
struct count
{
  using type = typename count_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence>;
  const static decltype(type::value) value = type::value;
};

template<typename Sequence>
using count_t = count<Sequence>;

}
}

#endif
