#ifndef FALCON_MPL_VALUE_TYPE_HPP
#define FALCON_MPL_VALUE_TYPE_HPP

#include <falcon/mpl/value_type_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename AssociativeSequence, typename T>
struct value_type
{
  using type = value_type_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence, T>::type;
};

}
}

#endif
