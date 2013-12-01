#ifndef FALCON_MPL_NEXT_PRIOR_HPP
#define FALCON_MPL_NEXT_PRIOR_HPP

namespace falcon {
namespace mpl {

template<typename T>
struct next
{ using type = typename T::next; };

template<typename T>
struct prior
{ using type = typename T::prior; };

template<typename T>
using next_t = typename next<T>::type;

template<typename T>
using prior_t = typename prior<T>::type;

}
}

#endif
