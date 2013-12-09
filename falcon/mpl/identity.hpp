#ifndef FALCON_MPL_IDENTITY_HPP
#define FALCON_MPL_IDENTITY_HPP

namespace falcon {
namespace mpl {

template<typename T>
struct identity
{ using type = T; };

}
}

#endif
