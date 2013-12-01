#ifndef FALCON_MPL_INSERT_HPP
#define FALCON_MPL_INSERT_HPP

#include <falcon/mpl/insert_fwd.hpp>
#include <falcon/mpl/sequence_tag.hpp>

namespace falcon {
namespace mpl {

template<typename Sequence, typename Pos_or_T, typename T>
struct insert
{
  using type = insert_impl<sequence_tag_t<Sequence>>
    ::template apply<Sequence, Pos_or_T, T>::type;
};

}
}

#endif
