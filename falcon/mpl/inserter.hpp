#ifndef FALCON_MPL_INSERTER_HPP
#define FALCON_MPL_INSERTER_HPP

namespace falcon {
namespace mpl {

template<typename Sequence, typename Operation>
struct inserter
{
  using state = Sequence;
  using operation = operation;
};

}
}

#endif
