#ifndef FALCON_MPL_IF_HPP
#define FALCON_MPL_IF_HPP

#include <falcon/type_traits/if.hpp>

namespace falcon {
namespace mpl {

template<bool B, typename T, typename U>
using if_c = ::falcon::if_<B, T, U>;

template<typename B, typename T, typename U>
using if_ = ::falcon::if_c<B, T, U>;

template<bool B, typename T, typename U>
using if_c_t = typename ::falcon::if_<B, T, U>::type;

template<typename B, typename T, typename U>
using if_t = typename ::falcon::if_c<B, T, U>::type;

}
}

#endif
