#ifndef FALCON_MPL_KEY_TYPE_HPP
#define FALCON_MPL_KEY_TYPE_HPP

#include <falcon/mpl/key_type_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename AssociativeSequence, typename Key>
struct key_type
{
  using type = key_type_impl<sequence_tag_t<AssociativeSequence>>
  ::template apply<AssociativeSequence, Key>::type;
};

}
}

#endif
