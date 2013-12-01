#ifndef FALCON_MPL_HAS_KEY_HPP
#define FALCON_MPL_HAS_KEY_HPP

#include <falcon/mpl/has_key_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename AssociativeSequence, typename Key>
struct has_key
{
  using type = has_key_impl<sequence_tag_t<AssociativeSequence>>
    ::template apply<AssociativeSequence, Key>::type;
};

}
}

#endif
