#ifndef FALCON_MPL_PAIR_HPP
#define FALCON_MPL_PAIR_HPP

namespace falcon {
namespace mpl {

template<typename T1, typename T2>
struct pair
{
  using type = pair;
  using first = T1;
  using second = T2;
};

}
}

#endif

