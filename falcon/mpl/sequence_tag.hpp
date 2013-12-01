#ifndef FALCON_MPL_SEQUENCE_TAG_HPP
#define FALCON_MPL_SEQUENCE_TAG_HPP

#include <falcon/sfinae/has_type.hpp>

namespace falcon {
namespace mpl {

namespace detail {
  template<typename Sequence, typename = void>
  struct sequence_tag_impl
  { using type = int; };

  template<typename Sequence>
  struct sequence_tag_impl<Sequence, FALCON_SFINAE_TYPE_PARAM(Sequence, tag)>
  { using type = typename Sequence::tag; };
}

template<typename Sequence>
struct sequence_tag
{ using type = typename detail::sequence_tag_impl<Sequence>::type; };

template<typename Sequence>
using sequence_tag_t = typename sequence_tag<Sequence>::type; 

}
}

#endif
