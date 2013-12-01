#ifndef FALCON_MPL_EMPTY_HPP
#define FALCON_MPL_EMPTY_HPP

#include <falcon/mpl/empty_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence>
struct empty
{
  using type = typename empty_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence>;
  const static decltype(type::value) value = type::value;
};

}
}

#endif
