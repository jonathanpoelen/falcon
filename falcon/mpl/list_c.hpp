#ifndef FALCON_MPL_LIST_C_HPP
#define FALCON_MPL_LIST_C_HPP

#include <falcon/mpl/list.hpp>
#include <falcon/mpl/integral.hpp>

namespace falcon {
namespace mpl {

template<typename T, T... Xs>
using list_c = list<integral_c<T, Xs>...>;

}
}

#endif
