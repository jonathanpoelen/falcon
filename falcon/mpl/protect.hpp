#ifndef FALCON_MPL_PROTECT_HPP
#define FALCON_MPL_PROTECT_HPP

namespace falcon {
namespace mpl {

template<typename T>
struct protect
{ using type = T; };

}
}

#endif
