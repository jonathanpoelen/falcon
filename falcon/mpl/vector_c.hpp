#ifndef FALCON_MPL_VECTOR_C_HPP
#define FALCON_MPL_VECTOR_C_HPP

#include <falcon/mpl/vector.hpp>
#include <falcon/mpl/integral_c.hpp>

namespace falcon {
namespace mpl {

template<typename T, T... Xs>
using vector_c = vector<integral_c<T, Xs>...>;

}
}

#endif
