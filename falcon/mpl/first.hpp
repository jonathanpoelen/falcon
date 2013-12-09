#ifndef FALCON_MPL_FIRST_HPP
#define FALCON_MPL_FIRST_HPP

namespace falcon {
namespace mpl {

template<typename Pair>
struct first
{ using type = typename Pair::first; };

template<typename Seq>
using first_t = typename first<Seq>::type;

}
}

#endif
