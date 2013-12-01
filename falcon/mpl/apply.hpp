#ifndef FALCON_MPL_APPLY_HPP
#define FALCON_MPL_APPLY_HPP

#include <falcon/mpl/aux_/apply.hpp>

namespace falcon {
namespace mpl {

template<typename F, typename... Args>
struct apply
{
  using type = typename aux::apply_impl<F, Args...>::type;
};

template<typename F, typename... Args>
using apply_t = typename apply<F, Args...>::type;

}
}

#endif
