#ifndef FALCON_MPL_SET_C_HPP
#define FALCON_MPL_SET_C_HPP

#include <falcon/mpl/set.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename T, T... Xs>
using set_c = set<integral_c<T, Xs>...>;

}
}

#endif
