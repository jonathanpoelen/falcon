#ifndef FALCON_MPL_IS_SAME_HPP
#define FALCON_MPL_IS_SAME_HPP

#include <falcon/mpl/integral_c.hpp>
#include <type_traits>

namespace falcon {
namespace mpl {

template<typename T, typename U>
struct is_same
{
  static const bool value = std::is_same<T, U>::value;
  using type = bool_<value>;
};

template<typename T, typename U>
using is_same_t = bool_<std::is_same<T, U>::value>;

}
}

#endif
