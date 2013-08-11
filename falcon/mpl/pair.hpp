#ifndef FALCON_MPL_PAIR_HPP
#define FALCON_MPL_PAIR_HPP

namespace falcon {
namespace mpl {

template<typename T1, typename T2>
struct pair
{
  typedef pair type;
  typedef T1 first;
  typedef T2 second;
};

}
}

#endif

