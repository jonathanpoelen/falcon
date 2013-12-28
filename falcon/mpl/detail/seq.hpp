#ifndef FALCON_MPL_DETAIL_SEQ_HPP
#define FALCON_MPL_DETAIL_SEQ_HPP

namespace falcon {
namespace mpl {
namespace detail {

template<typename Tag, typename... Args>
struct seq
{
  using type = seq;
  using tag = Tag;
};

}
}
}

#endif
