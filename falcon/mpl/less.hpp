#ifndef FALCON_MPL_LESS_HPP
#define FALCON_MPL_LESS_HPP

#include <falcon/mpl/integral_c.hpp>

namespace falcon {
namespace mpl {

template<typename T, typename U>
struct less
{
  static const bool value = (T::value < U::value);
  using type = bool_<value>;
};

template<typename T, typename U>
using less_t = bool_<(T::value < U::value)>;

}
}

#endif
