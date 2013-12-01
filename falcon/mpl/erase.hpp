#ifndef FALCON_MPL_ERASE_HPP
#define FALCON_MPL_ERASE_HPP

#include <falcon/mpl/erase_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename First, typename Last>
struct erase
{
  using type = erase_impl<sequence_tag_t<Sequence>>
    ::template apply< Sequence,First,Last >::type;
};

}
}

#endif
