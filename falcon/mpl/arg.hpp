#ifndef FALCON_MPL_ARG_HPP
#define FALCON_MPL_ARG_HPP

#include <falcon/arg/arg.hpp>

namespace falcon {
namespace mpl {

template<std::size_t N>
struct arg
{
  template<typename... Ts>
  using apply = arg_element<N-1, Ts...>;
};

}
}

#endif
