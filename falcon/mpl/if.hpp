#ifndef FALCON_MPL_IF_HPP
#define FALCON_MPL_IF_HPP

#include <falcon/type_traits/if.hpp>

namespace falcon {
namespace mpl {

template<typename C, typename TrueT, typename FalseT>
using if_ = ::falcon::if_c<C, TrueT, FalseT>;

template<bool c, typename TrueT, typename FalseT>
using if_c = ::falcon::if_<c, TrueT, FalseT>;

template<typename C, typename TrueT, typename FalseT>
using not_if = ::falcon::not_if_c<C, TrueT, FalseT>;

template<bool c, typename TrueT, typename FalseT>
using not_if_c = ::falcon::not_if<c, TrueT, FalseT>;

}
}

#endif
