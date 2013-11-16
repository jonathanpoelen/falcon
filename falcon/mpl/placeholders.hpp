#ifndef FALCON_MPL_PLACEHOLDERS_HPP
#define FALCON_MPL_PLACEHOLDERS_HPP

#include <falcon/mpl/detail/fwd.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

namespace placeholders {
template<std::size_t N>
struct placeholder
{
  typedef placeholder type;

  static const std::size_t value = N;

  template<typename Seq>
  using apply = at<Seq, int_<N-1> >;
};

using _1 = placeholder<1>;
using _2 = placeholder<2>;
using _3 = placeholder<3>;
using _4 = placeholder<4>;
using _5 = placeholder<5>;
using _6 = placeholder<6>;
using _7 = placeholder<7>;
using _8 = placeholder<8>;
using _9 = placeholder<9>;
}

}
}

#endif
