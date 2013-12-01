#ifndef FALCON_MPL_DETAIL_S_BACK_HPP
#define FALCON_MPL_DETAIL_S_BACK_HPP

#include <falcon/mpl/detail/s_at.hpp>
#include <falcon/mpl/detail/s_size.hpp>

namespace falcon {
namespace mpl {
namespace detail {

template<typename T>
struct s_back
: s_at<T, s_size<T>::value - 1>
{};

}
}
}

#endif
