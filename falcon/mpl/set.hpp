#ifndef FALCON_MPL_SET_HPP
#define FALCON_MPL_SET_HPP

#include <falcon/mpl/detail/fwd.hpp>

namespace falcon {
namespace mpl {

template<typename... Args>
struct set
: detail::mpl_container_def
{
  using type = set;
};

}
}

#endif
